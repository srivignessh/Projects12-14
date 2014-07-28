#include <msp430.h> // Specific device
#include <intrinsics.h> // Intrinsic functions
#include <stdint.h> // Integers of defined sizes

void main (void)
{
WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
// Capture either edge of CCI0B , synchronized , interrupts enabled
TACCTL0 = CM_3 | CCIS_1 | SCS | CAP | CCIE;
// Start timer: ACLK , no prescale , continuous mode , no ints , clear
TACTL = TASSEL_1 | ID_0 | MC_2 | TACLR;
for (;;) { // Loop forever with interrupts
__low_power_mode_3 (); // Only ACLK continues to run
}
}
// ----------------------------------------------------------------------
// Interrupt service routine for TACCR0.CCIFG , called on capture
// ----------------------------------------------------------------------
#pragma vector = TIMER0_VECTOR
__interrupt void TIMER0_ISR(void)
{
	P1OUT|=0x01;
}
