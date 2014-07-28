/*
 * _1s.c
 *
 * Created: 4/28/2013 3:43:39 AM
 *  Author: Administrator
 */ 


#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{	DDRB=0xFF;
    while(1)
    {
        PORTB=0x01;
		_delay_ms(5000);
		PORTB=0x00;
		_delay_ms(5000); 
    }
}