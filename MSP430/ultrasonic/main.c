#include "msp430g2553.h"
int x[5],i=0,k=0,flag=0;

void Transmit(char i)
{
	while (!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = i;
}
void Trigger()
{
	P1OUT|=0x10;
    _delay_cycles(1000);
    P1OUT&=~0x10;
}
unsigned long int Echo()
{

	unsigned long int p,r;
	for (p=0;p<600000;p++)
	{
		if(!(P1IN & 0x20))
		{
			continue;
		}
		else
			break;
	}
	if(p==600000)
		return 0;
	TAR=0;
	for(p=0;p<60000;p++)
	{
		if(P1IN & 0x20)
			{if(TAR>60000)
				break;
			 else
				continue;
			}
		else break;
	}
	if(p==60000)
	{
		return 10;
	}
	r=11;
	if(r>60000)
		return 1;
	else
		return r;
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
	for(i=0;i<5;i++)
	{
		x[i]=v%10;
		v=v/10;
	}
for(i=4;i>=0;i--)
	{	x[i]=x[i]+48;
		while (!(IFG2 & UCA0TXIFG)); // USART0 TX buffer ready?
		UCA0TXBUF = (x[i] & 0xFF00)>>8;
		while (!(IFG2 & UCA0TXIFG)); // USART0 TX buffer ready?
		UCA0TXBUF = (x[i] & 0x00FF);
	}


}

void main(void)
{

	WDTCTL = WDTPW + WDTHOLD;
    unsigned long int r;
	P1DIR|=0x41;
	P1REN |= BIT3;
	P1OUT |= BIT3;
    Uart_init();
      CCR0=65535;
      TACTL = TASSEL_2 + MC_1  + ID_3;
      _delay_cycles(2500000);
	while(1)
	{
		if(k%2==1)
			{
			Transmit('u');
			Trigger();
			r=Echo();
			r=r>>1;
			Value_send(r);
			}
		if(P1IN & 0x08)
		{
			P1OUT&=~0x01;
			flag=0;
		}
		else
		{
			if(flag==0)
			{
				flag=1;
				k++;
				P1OUT|=0x41;
				if(k%2==1)
				{	P1OUT|=0x01;
					Transmit('b');

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
