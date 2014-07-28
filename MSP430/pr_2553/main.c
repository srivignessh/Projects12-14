#include <msp430.h> 
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= 0x40;             // P1.6 to output
     P1SEL |= 0x40;             // P1.6 to TA0.1
     CCR0 = 65535;             // PWM Period
     CCTL1 = OUTMOD_7;          // CCR1 reset/set
     CCR1 = 32768;                // CCR1 PWM duty cycle
     TACTL = TASSEL_2 + MC_1  + ID_3;   // SMCLK, up mode, prescale by 8
     if(TACCR0);
	return 0;
}
