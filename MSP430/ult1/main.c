#include <msp430.h>
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= 0x01;					// Set P1.0 to output direction

	while(1) {
	    	P1OUT |= 0x01;
	    	_delay_cycles(1000);
	    	P1OUT &=~0x01;
	    	if(P1IN & 0x80);

	    	_delay_cycles(10000);

	}
	return 0;
}
