#include "msp430g2553.h"

#define LCM_DIR P1DIR
#define LCM_OUT P1OUT

//
// Define symbolic LCM - MCU pin mappings
// We've set DATA PIN TO 4,5,6,7 for easy translation
//
#define LCM_PIN_RS BIT0 // P1.0
#define LCM_PIN_EN BIT1 // P1.1
#define LCM_PIN_D7 BIT7 // P1.7
#define LCM_PIN_D6 BIT6 // P1.6
#define LCM_PIN_D5 BIT5 // P1.5
#define LCM_PIN_D4 BIT4 // P1.4


#define LCM_PIN_MASK ((LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_D7 | LCM_PIN_D6 | LCM_PIN_D5 | LCM_PIN_D4))

#define FALSE 0
#define TRUE 1

void PrintStr(char *Text);
void PrintNum(int integer);
void InitializeLcm(void);
void PulseLcm();
void SetCursorPos(char Row, char Col);
void SendByte(char ByteToSend, int IsData);
void ClearScr();
int T;

void ADC_init4()
{
	ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;  // P1.5 input, use ADC10CLK div 1, single channel mode
	    ADC10CTL1 =  INCH_3 + SHS_0 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_0;
	    ADC10AE0 = BIT3;      // Enable ADC input on P1.1
	    ADC10CTL0 |= ENC;     // Enable conversions.

}
int ADC_read()
{   unsigned int ADC;
	ADC10CTL0 |= ADC10SC;   // start a new conversion
				while ((ADC10CTL1 & ADC10BUSY) == 0x01);   // wait for conversion to end
				ADC=ADC10MEM;      // convert to volts and store
				return ADC;
}

//Scan the D0-D7 bits
void PulseLcm()
{

    LCM_OUT |= LCM_PIN_EN;
    __delay_cycles(200);

    LCM_OUT &= (~LCM_PIN_EN);
    __delay_cycles(200);
}



void SendByte(char ByteToSend, int IsData)
{

    // clear out all pins

    LCM_OUT &= (~LCM_PIN_MASK);


     //Send High nibble then low nibble
    LCM_OUT |= (ByteToSend & 0xF0);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }

    //Read D0-D7
    PulseLcm();


    LCM_OUT &= (~LCM_PIN_MASK);
    LCM_OUT |= ((ByteToSend & 0x0F) << 4);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }


    PulseLcm();
}


void SetCursorPos(char Row, char Col)
{
    char address;

    //
    // construct address from (Row, Col) pair
    //

    if (Row == 0)
    {
        address = 0x00;
    }
    else
    {
        address = 0x40;
    }

    address |= Col;
    SendByte(0x80 | address, FALSE);
}


void ClearScr()
{
    // Clear display(weird logic I used to make this work)

    SendByte(0x01, FALSE);
    PrintNum(50);
    SetCursorPos(0,0);
    PrintStr(" ");
    SetCursorPos(0,0);

}

void InitializeLcm(void)
{

    // set the MSP pin configurations
    // and bring them to low
    LCM_DIR |= LCM_PIN_MASK;
    LCM_OUT &= ~(LCM_PIN_MASK);

    // wait for the LCM to warm up and reach
    // active regions. Remember MSPs can power
    // up much faster than the LCM.

    _delay_cycles(100000);


    LCM_OUT &= ~LCM_PIN_RS;//RS and EN pulled low
    LCM_OUT &= ~LCM_PIN_EN;


    P1OUT=0x20;//Set 4 bit Mode

    PulseLcm();

    P1OUT=0x00;//Pull P1 low

    SendByte(0x28, FALSE);//For 4 bit Initialisation

    SendByte(0x0F, FALSE);//Cursor Blink

    SendByte(0x01, FALSE);//Clear Screen
}


void PrintNum(int integer)
{

    char thousands,hundreds,tens,ones;
    thousands = integer / 1000;
    if(thousands)
    SendByte((thousands + 0x30),TRUE);

    hundreds = ((integer - thousands*1000)-1) / 100;
    if(hundreds)
    SendByte((hundreds + 0x30),TRUE);

	tens=(integer%100)/10;
	if(tens)
    SendByte((tens + 0x30),TRUE);

    ones=integer%10;
	SendByte((ones + 0x30),TRUE);
}

void PrintStr(char *Text)
{
    char *c;
    c = Text;

    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, TRUE);
        c++;
    }
}

void pwm()
{

	 P2DIR |= BIT4;             // P1.6 to output
	 P2SEL |= BIT4;             // P1.6 to TA0.1
	 CCR0 = 255;             // PWM Period
	 CCTL1 = OUTMOD_7;          // CCR1 reset/set
	 TACTL = TASSEL_2 + MC_1  + ID_3;   // SMCLK, up mode, prescale by 8
}
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    ADC_init4();
    while(1)
    {
    InitializeLcm();
    _delay_cycles(1000);
    T=ADC_read();
    T=T/3;
    CCR1=255;
    PrintStr("Temperature");
    SetCursorPos(1,0);    //Go to second line start
    PrintNum(T);

    _delay_cycles(1000000);
    ClearScr();
    }

}
