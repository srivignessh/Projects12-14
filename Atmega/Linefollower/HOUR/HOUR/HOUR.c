#define F_CPU 16000000UL
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void straight()
{
	PORTB=0b10100101;
}
void back()
{
	PORTB=0b10101010;
}
void left()
{
	PORTB=0b10100100;
}
void right()
{
	PORTB=0b10100001;
}
void leftin()
{
	PORTB=0b10100110;
	while(bit_is_set(PINC,7));
	}
void rightin()
{
	PORTB=0b10101001;
	while(bit_is_set(PINC,7));
}
void stop()
{
	PORTB=0x00;
}
void discont()
{
	while(1)
	{
		if(bit_is_clear(PINC,2) && bit_is_clear(PINC,4) && bit_is_clear(PINC,3) && bit_is_clear(PINC,5))
		straight();
		else if(bit_is_set(PINC,2) || bit_is_set(PINC,4) || bit_is_set(PINC,3) || bit_is_set(PINC,5))
		break;
	}
}

int main(void)
{	DDRB=0xFF;
	DDRC=0x00;
	PORTC=0xFF;
	PORTB=0x00;
	
	while(1)
	{   
		
		if((bit_is_clear(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_set(PINC,3)) && (bit_is_clear(PINC,5)))
		straight();
		else if((bit_is_set(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_clear(PINC,3)) && (bit_is_clear(PINC,5)))
		left();
		else if((bit_is_clear(PINC,2)) && (bit_is_clear(PINC,4)) && (bit_is_set(PINC,3)) && (bit_is_set(PINC,5)))
		right();
		else if((bit_is_set(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_set(PINC,3)) && (bit_is_clear(PINC,5)))
		leftin();
		else if((bit_is_clear(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_set(PINC,3)) && (bit_is_set(PINC,5)) )
		rightin();
		else if ((bit_is_clear(PINC,2)) && (bit_is_clear(PINC,4)) && (bit_is_clear(PINC,3)) && (bit_is_clear(PINC,5)))
		discont();
		else if((bit_is_set(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_set(PINC,3)) && (bit_is_set(PINC,5)))
		stop();
	}
	
}