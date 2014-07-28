#include <msp430.h>
#include "Basic_config.h"
#include "UART.h"
unsigned int measure_2,measure,measure_1,up;
void Config_init()
{
P2DIR &=~BIT0;
P2SEL |=BIT0;
P2SEL2 &=~BIT0;

P2DIR |=BIT1;
P2OUT &= ~BIT1;

//***Timer1A? capture configuration
//rising & falling edge + synchronous + P2.0 (CCI1A) + capture + capture/compare interrupt enable
TA1CCTL0 |= CM_3 + CCIS_0 + CAP + CCIE ;
//select smclock for timer a source + make ta1ccr0 count continously up + no division
TA1CTL |= TASSEL_2 + MC_2 + ID_0;
_BIS_SR(GIE);
WDTCTL = WDTPW + WDTHOLD;
}

void main()
{
Config_init();
uart_init();
while (1){
up=1;
P2OUT &= ~BIT1;
delay_us(2);
P2OUT |=BIT1;
delay_us(10);
P2OUT &= ~BIT1;
delay_ms(1000);
}
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1A0(void)
{
if(up) //is this the rising edge?
{

measure_1=TA1CCR0; // take first time measure


}
else //is this the falling edge?
{
measure_2=TA1CCR0; //take second time measure
if (measure_2>measure_1)
{
measure=(measure_2-measure_1)/58; // microseconds / 58 = centimeters
}
else
uart_put_num(measure_1,0,0);
uart_puts("\r\n2:");
uart_put_num(measure_2,0,0);
uart_puts("\r\nDis:");
uart_put_num(measure,0,0);

// measure_2=TA1CCR0; //take second time measure
// measure=(measure_2-measure_1)/58; // microseconds / 58 = centimeters
}
up=!up; //if this was the rising edge, the next one will be a falling edge, and vice-versa
TA1CTL &= ~TAIFG; //clear timer A interrupt flag, so the chip knows we handled the interrupt
}
