#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR|=0x01;
    P1REN|=0x08;
    while(1)
    {
    	if(P1IN&0x08)
    P1OUT&=~0x01;
    else
    P1OUT|=0x01;
    }
	
	return 0;
}
