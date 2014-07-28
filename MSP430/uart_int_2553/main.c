#include "msp430g2553.h"

int ADC,x[4],i=0,k=0,flag=0,a=0,s=0;
Transmit(char i)
{
	while (!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = i;
}
void Uart_init()
{
	    BCSCTL1 = CALBC1_1MHZ; // Set DCO
		DCOCTL = CALDCO_1MHZ;
		P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
		P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD

	    UCA0CTL1 |= UCSSEL_2; // SMCLK
		UCA0BR0 = 104; // 1MHz 9600
		UCA0BR1 = 0; // 1MHz 9600
		UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
		UCA0CTL1 &= ~UCSWRST; // **Initialise USCI state machine**

}
void Value_send(int v)
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


}

void main(void)
{

	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR|=0x41; 		// Declare P1.0 as output
	P1REN |= BIT3;
	P1OUT |= BIT3;
    Uart_init();
	while(1)
	{
		if(k%2==1)
			{
			Transmit('u');
			a=1200;
			a=a>>2;
			Value_send(a);

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

