#include "msp430.h"

void main(void)
{
 int a;
 WDTCTL = WDTPW + WDTHOLD;  	// Stop WDT

 P1DIR |= 0x08;            		 // P1.6 to output
 P1SEL |= 0x08;            		 // P1.6 to TA0.1

 CCR0 = 200;           			   // PWM Period
 CCTL1 = OUTMOD_7;        		   // CCR1 reset/set
 TACTL = TASSEL_2 + MC_1  + ID_3;   	   // SMCLK, up mode, prescale by 8

while (1)
{
for(CCR1=0;CCR1<200;CCR1++)
 _delay_cycles(15000);

for(CCR1=200;CCR1>0;CCR1--)
_delay_cycles(15000);
}

}
