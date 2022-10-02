// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

//void waitMs1(){_delay_ms(1);}
//void waitMs(int ms){while (ms-->0){waitMs1();}}
//void waitSec(int sec){while (sec-->0){waitMs(1000);}}

void port_inti();
void ledOut(uint8_t leds);

void rgbLed();

uint8_t leds = 0x01;
uint8_t leds1 = 0x01;
uint8_t leds2 = 0x80;
uint8_t irany = 0x01;

int d = 500; // base delay time number

int main(void)
{
	port_inti();
	
	while (1)
	{
		//ledOut(leds);
		rgbLed();
	}
}
void rgbLed()
{
	// RED -> C7 (0x80), GREEN -> E2 (0x04), BLUE -> E3 (0x08)
	
	// RED
	PORTC = 0x88;
	_delay_ms(1000);
	PORTC = 0x00;
	
	// GREEN
	PORTE = 0x04;
	_delay_ms(1000);
	PORTE = 0x00;
	
	// BLUE
	PORTE = 0x08;
	_delay_ms(1000);
	PORTE = 0x00;

}

void port_inti()
{
	// Ha bit 1 akkor kimenet, ha bit 0 akkor bemenet
	
	DDRB = 0xF0;	// Led 0-3 -> 11110000
	DDRD = 0xF0;	// Led 4-7 - 11110000
	DDRG = 0x00;	// Pushbuttons K0-K4
	
	DDRC = 0x88;		// Keyboard, -> 10001000 || Red, KBD1row?
	DDRE = 0x0C;		// RGB led -> 00001100 || Green, Blue
}

void ledOut(uint8_t led)
{
	PORTD = led;
	PORTB = led << 4; // Shiftelni kell balra 4-el
}
