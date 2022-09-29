// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}

void port_inti();
void ledOut(uint8_t leds);
void balra_fut();
void jobbra_fut();
void balra_jobbra_fut();
void knight_rider();

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
		if (PING == 0x02) // if the 2. button is pressed increase by 100
		{
			d += 50;
			if (d > 10000) // delay protection
				d = 10000;
		}
		if (PING == 0x01) // if the 1. button is pressed decrease by 100
		{
			d -= 50;
			if (d < 50) // delay protection
				d = 50;
		}
		ledOut(leds);

		waitMs(d);
		knight_rider();
	}
}

void port_inti()
{
	DDRB = 0xF0;
	DDRD = 0xF0;
	DDRG = 0x00;
}

void ledOut(uint8_t led)
{
	PORTD = led;
	PORTB = led << 4; // Shiftelni kell balra 4-el
}

void balra_fut()
{
	if (leds == 0x80)
	{
		leds = 0x01;
	}
	else
	{
		leds = leds << 1;
	}
}

void jobbra_fut()
{
	if (leds == 0x01)
	{
		leds = 0x80;
	}
	else
	{
		leds = leds >> 1;
	}
}

void balra_jobbra_fut()
{
	if (irany)
	{
		if (leds == 0x80)
		irany = 0x00;
		else
		leds = leds << 1;
	}
	else
	{
		if (leds == 0x01)
		irany = 0x01;
		else
		leds = leds >> 1;
	}
}

void knight_rider()
{
	// balra fut
	if (leds1 == 0x80)
	{
		leds1 = 0x01;
	}
	else
	{
		leds1 = leds1 << 1;
	}

	// jobbra fut
	if (leds2 == 0x01)
	{
		leds2 = 0x80;
	}
	else
	{
		leds2 = leds2 >> 1;
	}

	leds = leds1 | leds2;
}