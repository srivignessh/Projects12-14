#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= 0x40;					// Set P1.0 to output direction

	for(;;) {
		P1OUT ^= 0x40;				// Toggle P1.0 using exclusive-OR
		 _delay_cycles(1000000);

	}
	
	return 0;
}
