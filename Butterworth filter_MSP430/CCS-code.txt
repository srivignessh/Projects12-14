#include <msp430.h>
unsigned int x[3]={0,0,0},ADC,i;
float y[3]={0,0,0};
float b[3]={0.025085630936916591, 0.050171261873833181, 0.025085630936916591};
float a[3]={1.2490750545127478, -1.9498287381261667, 0.80109620736108533};
void loop()
{
}

void ADC_init()
{
	ADC10CTL1 = INCH_3 + ADC10DIV_3 ; // Channel 5, ADC10CLK/4
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE; //Vcc & Vss as reference
	ADC10AE0 |= BIT3;     // Enable ADC input on P1.1
	ADC10CTL0 |= ENC + ADC10SC;   // start a new conversion
}
int ADC_read()
{
	ADC10CTL0 |= ADC10SC;   // start a new conversion
				while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
				ADC=ADC10MEM;      // convert to volts and store
				return ADC;
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
void Transmit(char i)
{
	while (!(IFG2 & UCA0TXIFG)); //Uart Buffer wait
	UCA0TXBUF = i;				//Uart Tx Buffer value set
}
void OutSend(int v)
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
	Transmit('\r');
	Transmit('\n');
	}

int main(void) {
	ADC_init();
	Uart_init();
	while(1)
	{
	  x[0]=x[1];x[1]=x[2];y[0]=y[1];y[1]=y[2];
      x[2] = ADC_read();;
	  y[2]=(x[2]*b[0]+x[1]*b[1]+x[0]*b[2]-a[1]*y[1]-a[2]*y[0])/a[0];
	  OutSend(y[2]);
	  _delay_cycles(1000);
	}
	return 0;
}
