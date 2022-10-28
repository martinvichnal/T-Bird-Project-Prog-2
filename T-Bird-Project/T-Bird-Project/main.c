#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "delay.h"
#include "led.h"
#include "matrix.h"
#include "rgb.h"
#include "sevenSegment.h"
#include "lcd.h"

// Ports/Timer/Interrupts initialization
void init();

int timerNum = 0;
uint8_t ido;
uint8_t b;

// Menu region. Contains Menus, sub menus and their pointer variables
#pragma region menu

// Main string menu system 1-4
const uint8_t M100[] = "<<Game>>\0";			//menu 1
const uint8_t M200[] ="<<Menu2>>\0";			//menu 2
const uint8_t M300[] ="<<Menu3>>\0";			//menu 3

// SubMenu strings within main menu.
/* Menu 1 sub menus */
const uint8_t M101[] ="Start\0";				// Start
/* Menu 2 sub menus */
const uint8_t M201[] ="R ON\0";				// Setting R led
const uint8_t M202[] ="G ON\0";				// Setting G led
const uint8_t M203[] ="B ON\0";				// Setting B led


// Pointers for menu strings
const uint8_t *MENU[] ={
	M100,							//menu 1 string
	M200,							//menu 2 string
	M300							//menu 3 string
};

// Pointers for sub menus
const uint8_t *SUBMENU[] ={
	M101, M201, M202, M203			//sub menus of menu 1
};


struct Menu_State{
	uint8_t menuNo;//1,2,3,4
	uint8_t subMenuNo;//1,2,3
}MN;

#pragma endregion menu


int main(void)
{
	init();
	
	lcd_init();
	lcd_write_cmd(0x01);
	lcd_Puts("Vichnal Martin");
	lcd_write_cmd(0xC0);
	lcd_Puts("Hello World!");
	
	rgb_Show(0, 0, 100, 100);
	
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
	rgb_pwm_handling();
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
	TIMSK = 1 << TOIE0;				// OverFlow enable
	sei();
}