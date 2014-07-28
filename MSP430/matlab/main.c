#include "msp430g2553.h"
#include<stdlib.h>
void sendstring(char * str)
{
int i = 0;
for(i = 0; i < strlen(str); i++)
{
while (!(IFG2&UCA0TXIFG)); // USART0 TX buffer ready?
UCA0TXBUF = str[i];
}
}

void main(void)

{
	char b[7];
	b[0]='0'+rand()%10;
	b[1]=' ';
	b[2]='0'+rand()%10;
	b[3]=' ';
	b[4]='0';
	b[5]='\n';
	b[6]='\0';
	int i=0;
	int adc_val2;
WDTCTL = WDTPW + WDTHOLD; // Stop WDT

P1DIR |= (BIT6); // Set the LEDs on P1.0, P1.1, P1.2 and P1.6 as outputs
P1OUT = 0x10;

BCSCTL1 = CALBC1_1MHZ; // Set DCO
DCOCTL = CALDCO_1MHZ;
P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
UCA0CTL1 |= UCSSEL_2; // SMCLK
UCA0BR0 = 104; // 1MHz 9600
UCA0BR1 = 0; // 1MHz 9600
UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
while(1)
{
	ADC10CTL0 = SREF_0+ADC10SHT_2 + ADC10ON; // Use Vcc/Vss for Up/Low Refs, 16 x ADC10CLKs, turn on ADC

ADC10CTL1 = INCH_0+SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;

ADC10AE0 |= 0x10 ; // PA.0 ADC option select

ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start

adc_val2=ADC10MEM/4;
	b[4]='0'+adc_val2%10;
	adc_val2=adc_val2/10;
	b[3]='0'+adc_val2%10;
	adc_val2=adc_val2/10;
	b[2]='0'+adc_val2%10;
	adc_val2=adc_val2/10;
	b[1]='0'+adc_val2%10;
	adc_val2=adc_val2/10;
	b[0]='0'+adc_val2%10;
	b[5]='\n';
	b[6]='\0';
	sendstring(b);
}
__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
}
