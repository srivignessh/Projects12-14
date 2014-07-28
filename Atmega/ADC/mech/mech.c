#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void ADC_init()
{
	ADMUX = (1<<REFS0) ; // Reference Voltage to Avcc= Vcc= 5 V
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

int ADC_read( uint8_t channel)
{
	channel = channel & 0b00000111; // Making sure that channel value is less than 7
	ADMUX|= channel; // Assigning channel value to MUX bits of ADMUX
	ADCSRA|= (1<<ADSC); // Start Conversion
	while( ! ( ADCSRA & (1<<ADIF) ) ); // Wait till the conversion completes
	ADCSRA|= (1<<ADIF); // Clear the ADIF bit by writing ‘1’
	return ADC;// Return the converted Digital value to the function
}

int main(void)
{
	float value;
	float temp;
	DDRB=0xFF;
	ADC_init();	// Initialization of ADC
	while(1)
	{
		value=ADC_read(0);
		temp=(value/1023)*5*100;
		if(temp>30 && temp<33)
		{PORTB=0x00;
		}		
		else
		{PORTB=0x01;
		}		
	}
}
