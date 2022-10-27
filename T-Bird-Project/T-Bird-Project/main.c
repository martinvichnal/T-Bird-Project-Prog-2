#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "delay.h"
#include "led.h"
#include "matrix.h"
#include "rgb.h"
#include "sevenSegment.h"


// Ports/Timer/Interrupts initialization
void init();

int timerNum = 0;
uint8_t ido;
uint8_t b;


int main(void)
{
	init();
	
	while (1)
	{
		//rgb_Show(0, 0, 100, 100);

		b = matrix();
		if (b <= 9)
		{
			PORTA = 0x80 | b;
		}
	}
}


ISR(TIMER0_OVF_vect)
{
	//rgb_pwm_handling();
	
	//sevenSegment_PutNumber(timerNum);
	

	if (!ido--)
	{
		// 7segmens szamlalo
		timerNum++;
		if (timerNum == 9999)
		{
			timerNum = 0;
		}
	}
}


void init()
{
	// 1 - output
	// 0 - input

	DDRB &= 0x0F;	// led mask	-> 00001111 (0 - 3)
	DDRB |= 0xF0;	// led		-> 11110000 (0 - 3)
	DDRD &= 0x0F;	// led mask	-> 00001111 (0 - 3)
	DDRD |= 0xF0;	// led		-> 11110000 (4 - 7)

	//DDRG = 0x00;	// Pushbuttons K0-K4
	DDRG &= 0xE0;	// Pushbuttons mask	-> 11100000	(K0 - K4)
	DDRG |= 0x00;	// Pushbuttons		-> 00000000 (K0 - K4)
	
	DDRE &= 0xF3;	// RGB mask	-> 11110011 (Blue & Green)
	DDRE |= 0x0C;	// RGB led	-> 00001100 (Blue & Green)
	DDRC &= 0x7F;	// RGB mask	-> 01111111 (Red)
	DDRC |= 80;		// RGB led	-> 10000000 (Red)
	
	DDRA = 0xFF;	// 7 Segment display
	
	// Matrix keyboard
	DDRC &= 0x80;	// Matrix mask	->	10000000
	DDRC |= 0x78;	// Matrix		->	01111000
	
	
	// Timer init:
	TCCR0 = 0 << CS02 | 1 << CS01 | 0 << CS00 | 1 << WGM00 | 1 << WGM01;
	//TCCR0 = 1 << CS01 | 1 << CS00;
	TIMSK = 1 << TOIE0;				// OverFlow enable
	sei();
	
}