#include "msp430.h"
void main(void)
{
int adc_val1 , adc_val2;
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P1DIR=0x20; // P1.5 to output
P2DIR|=0x07;
while(1)
{
ADC10CTL0 = SREF_0+ADC10SHT_2 + ADC10ON; // Use Vcc/Vss for Up/Low Refs, 16 x ADC10CLKs, turn on ADC
ADC10CTL1 = INCH_1+SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0; // P1.1 input, use ADC10CLK div 1, single channel mode
ADC10AE0 |= 0x02; // PA.1 ADC option select
ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
adc_val1=ADC10MEM;
adc_val1= adc_val1/4;
ADC10CTL0 = SREF_0+ADC10SHT_2 + ADC10ON; // Use Vcc/Vss for Up/Low Refs, 16 x ADC10CLKs, turn on ADC
ADC10CTL1 = INCH_0+SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0; // P1.0 input, use ADC10CLK div 1, single channel mode
ADC10AE0 |= 0x01; // PA.0 ADC option select
ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
adc_val2=ADC10MEM;
adc_val2= adc_val2/4;
if((adc_val1 >140)&&( adc_val2>140))
{
P1OUT|=BIT5;
P2OUT&=~0x07;
}
else if((adc_val1 >140)&&( adc_val2<120))
{
P1OUT&=~0x20;
P2OUT&=~0x05;
P2OUT|=0x02;
}
else if ((adc_val1 >140)&&( adc_val2>120)&& (adc_val2<140))
{
P1OUT|=BIT5;
P2OUT&=~0x05;
P2OUT|=BIT1;
}
else if (adc_val1 <120)
{
P1OUT&=~0x20;
P2OUT|=0x05;
P2OUT&=~0x02;
}
else
{
P1OUT&=~0x20;
P2OUT&=~0x05;
P2OUT&=~0x02;
}
}
}
