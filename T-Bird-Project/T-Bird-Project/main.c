// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

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

int main(void)
{
	// DDRB = 0xF0;
	// PORTB = 0xF0;
	port_inti();

	while (1)
	{
		if(PING == 0x01)
		{
			ledOut(leds);
			_delay_ms(500);

			// balra_jobbra_fut();

			// balra_fut();
			// jobbra_fut();

			// leds = leds<<1;
			// leds = leds^0x33; //XOR
			// PORTB = 0x00;
			//_delay_ms(500);

			knight_rider();
		}
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