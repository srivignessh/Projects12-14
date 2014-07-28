#include "msp430.h"
int ADC;
void main(void)
{
    P1DIR|=0x41;
    P1OUT|=0x41;
    WDTCTL = WDTPW + WDTHOLD;
            // Use Vcc/Vss for Up/Low Refs, 16 x ADC10CLKs, turn on ADC
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
            // P1.5 input, use ADC10CLK div 1, single channel mode
    ADC10CTL1 =  INCH_4 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
    ADC10AE0 = BIT4;      // Enable ADC input on P1.1
    ADC10CTL0 |= ENC;     // Enable conversions.

    while(1)
    {
    	P1OUT&=~0x41;
        ADC10CTL0 |= ADC10SC;   // start a new conversion
        while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
        ADC=ADC10MEM;      // convert to volts and store
        ADC=ADC>>2;
if(ADC<85)
P1OUT |= 0x01;
else if(ADC<170)
P1OUT |= 0x40;
else
P1OUT |= 0x41;
    }
}
