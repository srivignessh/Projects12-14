#include <msp430.h>
int ADC;
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
UCA0CTL1 &= ~UCSWRST;
}
void send(int v)
{ int i;
  char x[4];
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
Transmit('e');
}
void ADC_init()
{
	ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
	            // P1.5 input, use ADC10CLK div 1, single channel mode
	    ADC10CTL1 =  INCH_5 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
	    ADC10AE0 = BIT5;      // Enable ADC input on P1.1
	    ADC10CTL0 |= ENC;     // Enable conversions.
}
int ADC_read()
{		P1OUT&=~0x41;
		ADC10CTL0 |= ADC10SC;   // start a new conversion
	    while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
	    ADC=ADC10MEM;      // convert to volts and store
	    ADC=ADC>>2;
	    return ADC;
}
int main(void) {

	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= 0x01;				// Set P1.0 to output direction
		 Uart_init();
		 ADC_init();
		 int k=1;
		 Transmit('h');
		 int x;
	while(1) {
			P1OUT |= 0x01;
	    	_delay_cycles(1000);
	    	P1OUT &=~0x01;
	    	x=ADC_read();
	    	send(x);
	    	Transmit('g');
	    	_delay_cycles(1000000);
	   k=0;
	}

	return 0;
}
