#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
P1DIR=0x40;
while(1)
{P1OUT=0xFF;
_delay_cycles(5000000);
P1OUT=0x00;
_delay_cycles(5000000);
}
return 0;
}
