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

int main(void)
{	DDRB=0xFF;
	DDRC=0x03;
	PORTC=0x02;
	PORTB=0x00;
	straight();
	_delay_ms(500);
	while(1)
	{
		
		if((bit_is_clear(PINC,3)) && (bit_is_set(PINC,5)) && (bit_is_set(PINC,2)) && (bit_is_clear(PINC,4)))
		straight();
		else if(((bit_is_set(PINC,3)) && (bit_is_set(PINC,5)) && (bit_is_clear(PINC,2)) && (bit_is_clear(PINC,4)))||((bit_is_clear(PINC,3)) && (bit_is_set(PINC,5)) && (bit_is_clear(PINC,2)) && (bit_is_clear(PINC,4))))
		left();
		else if(((bit_is_clear(PINC,3)) && (bit_is_clear(PINC,5)) && (bit_is_set(PINC,2)) && (bit_is_set(PINC,4)))||((bit_is_clear(PINC,3)) && (bit_is_clear(PINC,5)) && (bit_is_set(PINC,2)) && (bit_is_clear(PINC,4))))
		right();
		else if((bit_is_set(PINC,3)) && (bit_is_set(PINC,5)) && (bit_is_set(PINC,2)) && (bit_is_clear(PINC,4)) && (bit_is_set(PINC,7)))
		leftin();
		else if((bit_is_clear(PINC,3)) && (bit_is_set(PINC,5)) && (bit_is_set(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_set(PINC,7)))
		rightin();
		else if((bit_is_set(PINC,3)) && (bit_is_set(PINC,5)) && (bit_is_set(PINC,2)) && (bit_is_set(PINC,4)) && (bit_is_clear(PINC,7)))
		{straight();
		_delay_ms(200);
		stop();}
		
	}
	
}