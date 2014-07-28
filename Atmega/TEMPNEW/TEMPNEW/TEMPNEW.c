/*
LCD DATA port----PORT D
signal port------PORT B
	rs-------PB0
	rw-------PB1
	en-------PB2
*/
#include<avr/io.h>
#include<util/delay.h>
#define LCD_DATA PORTD		//LCD data port

#define ctrl PORTB
#define en PB2		// enable signal
#define rw PB1		// read/write signal
#define rs PB0		// register select signal
void ADC_init()
{
	ADMUX = (1<<REFS0) ; // Reference Voltage to Avcc= Vcc= 5 V
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
} 
void init_LCD(void)
{
	LCD_cmd(0x38);		// initialization of 16X1 LCD in 8bit mode
	_delay_ms(1);
	
	LCD_cmd(0x01);		// clear LCD
	_delay_ms(1);
	
	LCD_cmd(0x0E);		// cursor ON
	_delay_ms(1);
	
	LCD_cmd(0x80);		// ---8 go to first line and --0 is for 0th position
	_delay_ms(1);
	return;
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

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA=cmd;
	ctrl =(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl =(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(50);
	return;
}
void LCD_write(unsigned char data)
{
	LCD_DATA= data;
	ctrl = (1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(50);
	return ;
}
void LCD_write_string(unsigned char *str)	//store address value of the string in pointer *str
{
	int i=0;
	char a;
	while(str[i]!='\0')				// loop will go on till the NULL character in the string
	{
		LCD_write(str[i]);				// sending data on LCD byte by byte
		i++;
	}
	a=248;
	LCD_write(a);
	a=67;
	LCD_write(a);
	return;
}
 
int main()
{
	DDRD=0xff;		
	DDRB=0x07;		
		_delay_ms(50);				// delay of 50 mili seconds
		ADC_init();					// initialization of ADC
		/*variable init*/
		int value;
		int temp;
		char str[5];
		
		while(1)
		{	value=0;temp=0;
			init_LCD();				// initialization of LCD
			value=ADC_read(0);		// function to read the Adc value
			temp=(value/1023)*5*100;	// temp=100*voltage
			sprintf(str, "%d", temp);	// function to convert int to string
			LCD_write_string(str);	// function to print string on LCD
			_delay_ms(5000);        // delay for visual 
		}		
				
	return 0;
}
 
