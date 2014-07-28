#include "msp430.h"
#include "stdbool.h"
int flag=0,ADC,x[4],i,k=0;
#define TXD BIT1 // TXD on P1.1
#define RXD BIT2 // RXD on P1.2

#define Bit_time 104 // 9600 Baud, SMCLK=1MHz (1MHz/9600)=104
#define Bit_time_5 52 // Time for half a bit.

unsigned char BitCnt; // Bit count, used when transmitting byte
unsigned char TXByte; // Value sent over UART when Transmit() is called
unsigned char RXByte; // Value recieved once hasRecieved is set


bool isReceiving; // Status for when the device is receiving
bool hasReceived; // Lets the program know when a byte is received

// Function Definitions
void Transmit(void);
void start()
{
	TXByte='b';
	Transmit();
}
void stop()
{
	TXByte='e';
	Transmit();
}
void ADC_init5()
{
	ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;  // P1.5 input, use ADC10CLK div 1, single channel mode
	    ADC10CTL1 =  INCH_5 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
	    ADC10AE0 = BIT5;      // Enable ADC input on P1.1
	    ADC10CTL0 |= ENC;     // Enable conversions.

}
void ADC_init4()
{
	ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;  // P1.5 input, use ADC10CLK div 1, single channel mode
	    ADC10CTL1 =  INCH_4 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
	    ADC10AE0 = BIT4;      // Enable ADC input on P1.1
	    ADC10CTL0 |= ENC;     // Enable conversions.

}
int ADC_read()
{
	ADC10CTL0 |= ADC10SC;   // start a new conversion
				while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
				ADC=ADC10MEM;      // convert to volts and store
				return ADC;
}
void ADC_Send_acc(int ad)
{	TXByte='a';
	Transmit();
	for(i=0;i<4;i++)
	{
		x[i]=ad%10;
		ad=ad/10;

	}
	for(i=3;i>=0;i--)
	{
	TXByte =x[i]+48;
	Transmit();
	}
}
void ADC_Send_str(int ad)
{	TXByte='s';
	Transmit();
	for(i=0;i<4;i++)
	{
		x[i]=ad%10;
		ad=ad/10;

	}
	for(i=3;i>=0;i--)
	{
	TXByte =x[i]+48;
	Transmit();
	}
}
void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop WDT

P1SEL |= TXD;
P1DIR |= TXD;

P1IES |= RXD; // RXD Hi/lo edge interrupt
P1IFG &= ~RXD; // Clear RXD (flag) before enabling interrupt
P1IE |= RXD; // Enable RXD interrupt



isReceiving = false; // Set initial values
hasReceived = false;

__bis_SR_register(GIE); // interrupts enabled

P1DIR|=0x41; 		// Declare P1.0 as output
P1REN|=0x08; 		//To enable pull up/pull down feature
P1OUT|=0x08;        // To pull-up P1.3

while(1)
{
	if(k%2==1)
		{
		ADC_init5();
		ADC=ADC_read();
		ADC_Send_acc(ADC);
		ADC_init4();
		ADC=ADC_read();
		ADC_Send_str(ADC);
		}
	if(P1IN&0x08)
	{
	P1OUT&=~0x01;	//Turn-off LED on P1.0
	flag=0;
	}
	else
	{
		if(flag==0)
		{
			flag=1;
			P1OUT|=0x41;//Turn-on LED on P1.0
			k++;
			if(k%2==1)
			{	start();
				ADC_init5();
				ADC=ADC_read();
				ADC_Send_acc(ADC);
				ADC_init4();
				ADC=ADC_read();
				ADC_Send_str(ADC);

			}
			if(k%2==0)
			{	P1OUT&=~0x40;
				stop();
			}
		}

	}



 // Load the recieved byte into the byte to be transmitted




}

    // __bis_SR_register(CPUOFF + GIE);
// LPM0, the ADC interrupt will wake the processor up. This is so that it does not
// endlessly loop when no value has been Received.

}

// Function Transmits Character from TXByte
void Transmit()
{
while(isReceiving); // Wait for RX completion
   CCTL0 = OUT; // TXD Idle as Mark
   TACTL = TASSEL_2 + MC_2; // SMCLK, continuous mode

   BitCnt = 0xA; // Load Bit counter, 8 bits + ST/SP
   CCR0 = TAR; // Initialize compare register

   CCR0 += Bit_time; // Set time till first bit
   TXByte |= 0x100; // Add stop bit to TXByte (which is logical 1)
   TXByte = TXByte << 1; // Add start bit (which is logical 0)

   CCTL0 = CCIS0 + OUTMOD0 + CCIE; // Set signal, intial value, enable interrupts
   while ( CCTL0 & CCIE ); // Wait for previous TX completion
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

isReceiving = true;

P1IE &= ~RXD; // Disable RXD interrupt
P1IFG &= ~RXD; // Clear RXD IFG (interrupt flag)

   TACTL = TASSEL_2 + MC_2; // SMCLK, continuous mode
   CCR0 = TAR; // Initialize compare register
   CCR0 += Bit_time_5; // Set time till first bit
CCTL0 = OUTMOD1 + CCIE; // Dissable TX and enable interrupts

RXByte = 0; // Initialize RXByte
BitCnt = 0x9; // Load Bit counter, 8 bits + ST
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
if(!isReceiving)
{
CCR0 += Bit_time; // Add Offset to CCR0
if ( BitCnt == 0) // If all bits TXed
{
   TACTL = TASSEL_2; // SMCLK, timer off (for power consumption)
CCTL0 &= ~ CCIE ; // Disable interrupt
}
else
{
CCTL0 |= OUTMOD2; // Set TX bit to 0
if (TXByte & 0x01)
CCTL0 &= ~ OUTMOD2; // If it should be 1, set it to 1
TXByte = TXByte >> 1;
BitCnt --;
}
}
else
{
CCR0 += Bit_time; // Add Offset to CCR0
if ( BitCnt == 0)
{
   TACTL = TASSEL_2; // SMCLK, timer off (for power consumption)
CCTL0 &= ~ CCIE ; // Disable interrupt

isReceiving = false;

P1IFG &= ~RXD; // clear RXD IFG (interrupt flag)
P1IE |= RXD; // enabled RXD interrupt

if ( (RXByte & 0x201) == 0x200) // Validate the start and stop bits are correct
{
RXByte = RXByte >> 1; // Remove start bit
RXByte &= 0xFF; // Remove stop bit
hasReceived = true;
}
   __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues
}
else
{
if ( (P1IN & RXD) == RXD) // If bit is set?
RXByte |= 0x400; // Set the value in the RXByte
RXByte = RXByte >> 1; // Shift the bits down
BitCnt --;
}
}
}
