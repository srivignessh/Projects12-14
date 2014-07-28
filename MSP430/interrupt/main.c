#include <msp430.h>
int main()
{
WDTCTL = WDTPW + WDTHOLD;
P1DIR|=0x01;  P1OUT &=~0x01;     	// Declare P1.0 as output and make it Low

P1DIR&=~0x08;     	//P1.4 input
P1REN|=0x08;     	// Enabling Pull up or down
P1OUT|=0x08;     	//Pull up P1,4

P1IE|=0x08;       	//Enable external interrupt
P1IES|=0x08;      	//Falling edge
_enable_interrupt(); 	//Enable global interrupt

while(1) { }
return 0;
}
//Interrupt block
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^=0x01;	  //Toggle LED on P1.0
P1IFG&=~0x10; 	 //Clear Flag
}
