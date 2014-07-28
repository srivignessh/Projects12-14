
#include <msp430.h>				

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= 0x01;					// Set P1.0 to output direction

	while(1) {
	    	P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR
		 _delay_cycles(1000000);

	}
	
	return 0;
}
