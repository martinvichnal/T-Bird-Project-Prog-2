// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void init();
void sevenSegment_PutDigit(uint8_t digit, uint8_t num);
void sevenSegment_PutNumber(int num);
void ledOut(uint8_t leds);
void rgbLed(double d);

void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}

uint8_t leds = 0x01;
uint8_t ido;
uint8_t digit[4] = {0};		int j = 0;

double d = 1000;



int main(void)
{
	init();
	
	sevenSegment_PutDigit(2,1);
	

	while (1)
	{
		
	}
}

ISR(TIMER0_OVF_vect)
{
	sevenSegment_PutNumber(1234);
	if (!ido--)
	{
		ledOut(leds);
		leds = leds ^ 0x01;
	}
}



void init()
{
	// Ha bit 1 akkor kimenet, ha bit 0 akkor bemenet
	
	DDRB = 0xF0;	// Led 0-3 -> 11110000
	DDRD = 0xF0;	// Led 4-7 - 11110000
	DDRG = 0x00;	// Pushbuttons K0-K4
	
	DDRC = 0x88;	// Keyboard, -> 10001000 || Red, KBD1row?
	DDRE = 0x0C;	// RGB led -> 00001100 || Green, Blue
	
	DDRA = 0xFF;	// 7 Segment display
	
	
	// Timer init:
	//TCCR0 = 1 << CS02 | 0 << CS01 | 0 << CS00;
	TCCR0 = 1 << CS01 | 1 << CS00;
	TIMSK = 1 << TOIE0;
	sei();
}

void sevenSegment_PutDigit(uint8_t digit, uint8_t num)
{
	if (digit > 3)
		return;
	if (num > 9)
		return;

	PORTA = 0x80 | (digit) << 4 | num;
}

void sevenSegment_PutNumber(int num)
{
	// Digit valaszto:			// Helyiertekek
	digit[0] = num%10;			// egyes
	digit[1] = (num/10)%10;		// tizes
	digit[2] = (num/100)%10;	// szazas
	digit[3] = (num/1000)%10;	// ezrese
	
	j = (j + 1) % 4;			// Hany Digites
	sevenSegment_PutDigit(j, digit[j]);
	
}

void ledOut(uint8_t led)
{
	PORTD = (led & 0xF0);
	PORTB = ((led << 4) & 0xF0);
}

void rgbLed(double d)
{
	// RED -> C7 (0x80), GREEN -> E2 (0x04), BLUE -> E3 (0x08)
	
	// RED
	PORTC = 0x88;
	//_delay_ms(1000);
	waitMs(d);
	PORTC = 0x00;
	
	// GREEN
	PORTE = 0x04;
	//_delay_ms(1000);
	waitMs(d);
	PORTE = 0x00;
	
	// BLUE
	PORTE = 0x08;
	//_delay_ms(1000);
	waitMs(d);
	PORTE = 0x00;

}