// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void port_inti();
void ledOut(uint8_t leds);
void timer_init();
void rgbLed(double d);

void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}

uint8_t leds = 0x01;
uint8_t ido;

double d = 1000;

int main(void)
{
	port_inti();
	timer_init();

	DDRA = 0xFF;
	PORTA = 0b10000001;
	
	while (1)
	{
		if (PING == 0x02) // if the 2. button is pressed increase by 100
		{
			d += 200;
			if (d > 10000) // delay protection
			d = 10000;
		}
		if (PING == 0x01) // if the 1. button is pressed decrease by 100
		{
			d -= 200;
			if (d < 50) // delay protection
			d = 50;
		}
		rgbLed(d);
	}
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
	PORTD = (led & 0xF0);
	PORTB = ((led << 4) & 0xF0);
}


void timer_init()
{
	TCCR0 = 1 << CS02 | 0 << CS01 | 0 << CS00;
	TIMSK = 1 << TOIE0;
	sei();
}

ISR(TIMER0_OVF_vect)
{
	if (!ido--)
	{
		ledOut(leds);
		leds = leds ^ 0x01;
	}
}