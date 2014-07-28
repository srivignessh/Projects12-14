#include "msp430g2553.h"

int ADC,x[4],i=0,k=0,flag=0,a=0,s=0;
void ADC_send(int v)
{

	for(i=0;i<4;i++)
	{
		x[i]=v%10;
		v=v/10;
	}
for(i=3;i>=0;i--)
	{
		x[i]= x[i]+48;
		while (!(IFG2 & UCA0TXIFG)); // USART0 TX buffer ready?
		UCA0TXBUF = (x[i] & 0xFF00)>>8;
		while (!(IFG2 & UCA0TXIFG)); // USART0 TX buffer ready?
		UCA0TXBUF = (x[i] & 0x00FF);
	}
}

void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR|=0x41; 		// Declare P1.0 as output
		//P1REN |= BIT3;
		//P1OUT |= BIT3;

		BCSCTL1 = CALBC1_1MHZ; // Set DCO
		DCOCTL = CALDCO_1MHZ;
		P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
		P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD

		UCA0CTL1 |= UCSSEL_2; // SMCLK
		UCA0BR0 = 52; // 1MHz 9600
		UCA0BR1 = 0; // 1MHz 9600
		UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
		UCA0CTL1 &= ~UCSWRST; // **Initialise USCI state machine**
	    P1OUT |=BIT6+BIT0;
	           		// Use Vcc/Vss for Up/Low Refs, 16 x ADC10CLKs, turn on ADC
	    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
	              		//  use ADC10CLK div 1, single channel mode
	    ADC10CTL1 =  INCH_5 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
	    ADC10AE0 = BIT5;      	// Enable ADC input on P1.5
	    ADC10CTL0 |= ENC;     	// Enable conversions.
	    while(1)
	       {
	           ADC10CTL0 |= ADC10SC;  		 	// start a new conversion
	           while ((ADC10CTL1 & ADC10BUSY) == 0x01);   	// wait for conversion to end
	            ADC=ADC10MEM;      			// convert to volts and store

	           a=ADC/4;
	           ADC_send(a);
}
}
