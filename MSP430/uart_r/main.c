#include "msp430g2553.h"

int ADC,x[4],i=0,k=0,flag=0,a=0,s=0;
int ADC_read()
{
	while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
	ADC=ADC10MEM;      // convert to volts and store
	return ADC;
}
Transmit(char i)
{
	while (!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = i;
}
void ADC_init5()
{
	ADC10CTL1 = INCH_5; // Channel 5, ADC10CLK/4
	ADC10CTL0 |= ENC + ADC10SC;   // start a new conversion
	Transmit('a');

}
void ADC_init4()
{
	ADC10CTL1 = INCH_4; // Channel 5, ADC10CLK/4
	ADC10CTL0 |= ENC + ADC10SC; // start a new conversion
	Transmit('s');
}
void ADC_send(int v)
{
	for(i=0;i<4;i++)
	{
		x[i]=v%10;
		v=v/10;
	}
for(i=3;i>=0;i--)
	{	x[i]=x[i]+48;
		while (!(IFG2 & UCA0TXIFG)); // USART0 TX buffer ready?
		UCA0TXBUF = (x[i] & 0xFF00)>>8;
		while (!(IFG2 & UCA0TXIFG)); // USART0 TX buffer ready?
		UCA0TXBUF = (x[i] & 0x00FF);
	}
ADC10CTL0 &= ~ENC;

}

void main(void)
{

	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR|=0x41; 		// Declare P1.0 as output
	P1REN |= BIT3;
	P1OUT |= BIT3;

	BCSCTL1 = CALBC1_1MHZ; // Set DCO
	DCOCTL = CALDCO_1MHZ;
	P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD

	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 104; // 1MHz 9600
	UCA0BR1 = 0; // 1MHz 9600
	UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST; // **Initialise USCI state machine**

	ADC10CTL1 = ADC10DIV_3; // Channel 5, ADC10CLK/4
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE; //Vcc & Vss as reference
	ADC10AE0 |= BIT5 + BIT4;     // Enable ADC input on P1.1

	while(1)
	{
		if(k%2==1)
			{
			ADC_init5();
			a=ADC_read();
			ADC_send(a);

			ADC_init4();
			s=ADC_read();
			ADC_send(s);
			_delay_cycles(1000000);

			}
		if(P1IN & 0x08)
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
				{	Transmit('b');

				}
				if(k%2==0)
				{
					P1OUT&=~0x40;
					Transmit('e');
				}
			}
		}
	}
}

