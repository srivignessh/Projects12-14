/******************************************************************************
 *                        MSP430G2553 printf() Tests
 *
 * Description: A modified version of the test code for testing oPossum's
 *              tiny printf() function. More information on the printf()
 *              function can be found at the following link.
 *
 *              http://www.43oh.com/forum/viewtopic.php?f=10&t=1732
 *
 *              This specific code tests the printf() function using
 *              the hardware UART on the MSP430G2553 with a baud rate
 *              of 9600. Once the character 't' is received, the test
 *              sequence is started.
 *
 *              This code was originally created for "NJC's MSP430
 *              LaunchPad Blog".
 *
 * Author:  Nicholas J. Conn - http://msp430launchpad.com
 * Email:   webmaster at msp430launchpad.com
 * Date:    06-07-12
 ******************************************************************************/

#include  "msp430g2553.h"
#include "stdarg.h"

// Define flags used by the interrupt routines
#define TX	BIT0

// Flag register
volatile unsigned char FLAGS = 0;

void sendByte(unsigned char);
void printf(char *, ...);
void initTimer(void);
void initUART(void);

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;			// Stop WDT

	initTimer();
	initUART();

	// Initialize values to display
	char *s = "NJC's MSP430 LaunchPad Blog";
	char c = '!';
	int i = -12345;
	unsigned u = 4321;
	long int l = -123456780;
	long unsigned n = 1098765432;
	unsigned x = 0xABCD;

	while(1) {
		switch(FLAGS) {
			case 0:										// No flags set
				__bis_SR_register(LPM3_bits + GIE);		// Enter LPM3
				break;
			case TX:						// Values need to be transmitted
				// Display all the different types of values
			    printf("String         %s\r\n", s);
			    printf("Char           %c\r\n", c);
			    printf("Integer        %i\r\n", i);
			    printf("Unsigned       %u\r\n", u);
			    printf("Long           %l\r\n", l);
			    printf("uNsigned loNg  %n\r\n", n);
			    printf("heX            %x\r\n", x);

				FLAGS &= ~TX;				// Clear transmit flag
				break;
		}
	}
}

/**
 * Initializes the timer to call the interrupt every 1 second
 */
void initTimer(void) {
	P1DIR |= BIT0;						// set P1.0 (LED1) as output
	P1OUT |= BIT0;						// P1.0 low
	CCTL0 = CCIE;						// CCR0 interrupt enabled
	CCR0 = 4096;						// 32kHz/8/4096 -> 1 sec
	TACTL = TASSEL_1 + ID_3 + MC_1;		// ACLK, /8, upmode
}

/**
 * Initializes the UART for 9600 baud with a RX interrupt
 **/
void initUART(void) {
	P1SEL = BIT1 + BIT2 ;				// P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;				// P1.1 = RXD, P1.2=TXD

	UCA0CTL1 |= UCSSEL_1;				// CLK = ACLK
	UCA0BR0 = 0x03;						// 32kHz/9600 = 3.41
	UCA0BR1 = 0x00;
	UCA0MCTL = UCBRS1 + UCBRS0;			// Modulation UCBRSx = 3
	UCA0CTL1 &= ~UCSWRST;				// **Initialize USCI state machine**
	IE2 |= UCA0RXIE;					// Enable USCI_A0 RX interrupt
}

/**
 * puts() is used by printf() to display or send a string.. This function
 *     determines where printf prints to. For this case it sends a string
 *     out over UART, another option could be to display the string on an
 *     LCD display.
 **/
void puts(char *s) {
	char c;

	// Loops through each character in string 's'
	while (c = *s++) {
		sendByte(c);
	}
}
/**
 * puts() is used by printf() to display or send a character. This function
 *     determines where printf prints to. For this case it sends a character
 *     out over UART.
 **/
void putc(unsigned b) {
	sendByte(b);
}

/**
 * Sends a single byte out through UART
 **/
void sendByte(unsigned char byte )
{
	while (!(IFG2&UCA0TXIFG));			// USCI_A0 TX buffer ready?
	UCA0TXBUF = byte;					// TX -> RXed character
}

/**
 * Interrupt routine for receiving a character over UART
 **/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	char r = UCA0RXBUF;					// Get the received character
	if (r == 't')						// 'u' received?
	{
		FLAGS |= TX;					// Set flag to transmit data
		__bic_SR_register_on_exit(LPM3_bits);	// Wake-up CPU
	}
}
/**
 * Timer A0 interrupt service routine, is called every second
 **/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= BIT0;					// Toggle LED
}
