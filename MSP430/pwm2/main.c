
#include "msp430.h"
int ADC;
void main(void)
{
	  WDTCTL = WDTPW + WDTHOLD;
 P1DIR |= BIT2;             // P1.6 to output
 P1SEL |= BIT2;             // P1.6 to TA0.1
 CCR0 = 255;             // PWM Period
 CCTL1 = OUTMOD_7;          // CCR1 reset/set
 TACTL = TASSEL_2 + MC_1  + ID_3;   // SMCLK, up mode, prescale by 8
//CCR1 = 200;
 //_BIS_SR(LPM0_bits);        // Enter LPM0

            // Use Vcc/Vss for Up/Low Refs, 16 x ADC10CLKs, turn on ADC
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
            // P1.5 input, use ADC10CLK div 1, single channel mode
    ADC10CTL1 =  INCH_3 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
    ADC10AE0 = BIT3;      // Enable ADC input on P1.1
    ADC10CTL0 |= ENC;     // Enable conversions.

    while(1)
    {
    	ADC10CTL0 |= ADC10SC;   // start a new conversion
        while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
        ADC=ADC10MEM;      // convert to volts and store
    	CCR1=5*(ADC-85);                // CCR1 PWM duty cycle
    }

}
