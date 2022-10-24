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
		b = matrix();
		if (b <= 9)
		{
			PORTA = 0x80 | b;
		}
	}
}


ISR(TIMER0_OVF_vect)
{
	//if (rgb_enable)
	//{
		//h_red++;
		//h_green++;
		//h_blue++;
		//
		//// Switching the RED led with PWM
		//if (h_red > pwm_red)
		//{
			//PORTC &=~ (1<<PC7);
			//if (h_red > 100)
			//h_red = 0;
		//}
		//else { PORTC |= (1<<PC7); }
//
		//// Switching the GREEN led with PWM
		//if (h_green > pwm_green)
		//{
			//PORTE &=~ (1<<PE2);
			//if (h_green > 100)
			//h_green = 0;
		//}
		//else { PORTE |= (1<<PE2); }
		//
		//// Switching the BLUE led with PWM
		//if (h_blue > pwm_blue)
		//{
			//PORTE &=~ (1<<PE3);
			//if (h_blue > 100)
			//h_blue = 0;
		//}
		//else { PORTE |= (1<<PE3); }
	//}
	
	sevenSegment_PutNumber(timerNum);
	

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
	// Ha bit 1 akkor kimenet, ha bit 0 akkor bemenet
	
	DDRB &= 0x0F;	// Mask 0b00001111
	DDRB |= 0xF0;	// Led 0-3 -> 11110000
	DDRD &= 0x0F;	// Mask 0b00001111
	DDRD |= 0xF0;	// Led 4-7 - 11110000

	DDRG = 0x00;	// Pushbuttons K0-K4
	
	//DDRC = 0x88;	// Keyboard, -> 10001000 || Red, KBD1row?

	DDRE = 0x0C;	// RGB led -> 00001100 || Green, Blue
	
	DDRA = 0xFF;	// 7 Segment display
	
	// Matrix billentyuzet
	DDRC &= 0x80;	// Maszk beallitasa hogy az elozot ne irjuk felul
	DDRC |= 0x78;	// 78 ha csak a matrixot hasznaljuk
	
	
	
	// Timer init:
	TCCR0 = 0 << CS02 | 1 << CS01 | 0 << CS00 | 1 << WGM00 | 1 << WGM01;
	//TCCR0 = 1 << CS01 | 1 << CS00;
	TIMSK = 1 << TOIE0;				// OverFlow enable
	sei();
	
}