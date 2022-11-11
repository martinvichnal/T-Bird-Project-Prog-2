#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "matrix.h"
#include "rgb.h"
#include "sevenSegment.h"


// Initializing ports, timers, interrupts
void init();
uint8_t counter = 0;		// Counter for Timer 1

// Parameters, functions for gameplay
void game();
int gameplay = 0;
int kor = 0;
int indicator = 0;


// Parameters, functions for generating a random number
int rnd_new();
#define rndMax 6
#define rndMin 1
uint8_t rnd = rndMin;
int number = 0;



// Menu region. Contains Menus, sub menus and their pointer variables
#pragma region menu

// Main string menu system 1-4
const uint8_t M100[] ="<<Game>>\0";		//menu 1
const uint8_t M200[] ="<<Menu2>>\0";	//menu 2
const uint8_t M300[] ="<<Menu3>>\0";	//menu 3

// SubMenu strings within main menu.
/* Menu 1 sub menus */
const uint8_t M101[] ="Start\0";	// Start
/* Menu 2 sub menus */
const uint8_t M201[] ="R ON\0";		// Setting R led
const uint8_t M202[] ="G ON\0";		// Setting G led
const uint8_t M203[] ="B ON\0";		// Setting B led


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


struct menuState{
	uint8_t menuNum;
	uint8_t subMenuNum;
}MN;

#pragma endregion menu

// Player struct
#pragma region player

struct playerState{
	uint8_t playerID;
	uint8_t playerHealth;
	uint8_t playerRandomDiceNum;
	uint8_t playerState;
}PS;

#pragma endregion player




int tmpRndNum = 0;

int main(void)
{
	init();
	lcd_init();
	
	rgb_Show(255, 0, 0, 255);
	
	while (1)
	{
		tmpRndNum = rnd_new();
		_delay_ms(1);
	}
}


// Timer 0 for controlling RGB leds with PWM
ISR(TIMER0_OVF_vect)
{
	rgb_pwm_handling();
}


// Timer 1 mainly used for seven segment display
ISR(TIMER1_OVF_vect) 
{
	sevenSegment_PutNumber(tmpRndNum);
	counter++;
	if (!counter)
	{
		PORTD ^= (1 << PB7); // flips the state of PD6
	}
}

// Initializing ports
void init()
{
	// 1 - output
	// 0 - input

	// LEDS
	DDRB &= 0x0F;	// led mask	-> 00001111 (0 - 3)
	DDRB |= 0xF0;	// led		-> 11110000 (0 - 3)
	DDRD &= 0x0F;	// led mask	-> 00001111 (0 - 3)
	DDRD |= 0xF0;	// led		-> 11110000 (4 - 7)

	// PUSHBUTTONS
	DDRG &= 0xE0;	// Pushbuttons mask	-> 11100000	(K0 - K4)
	DDRG |= 0x00;	// Pushbuttons		-> 00000000 (K0 - K4)
	
	// RGB LEDS
	DDRE &= 0xF3;	// RGB mask	-> 11110011 (Blue & Green)
	DDRE |= 0x0C;	// RGB led	-> 00001100 (Blue & Green)
	DDRC &= 0x7F;	// RGB mask	-> 01111111 (Red)
	DDRC |= 80;		// RGB led	-> 10000000 (Red)
	
	// 7 SEGMENT DISPLAY
	DDRA = 0xFF;	// 7 Segment display
	
	// MATRIX KEYBOARD
	DDRC &= 0x80;	// Matrix mask	->	10000000
	DDRC |= 0x78;	// Matrix		->	01111000
	
	
	// TIMER 0 INIT
	TCCR0 = 0 << CS02 | 0 << CS01 | 1 << CS00;
	TIMSK |= 1 << TOIE0;			// OverFlow enable
	sei();							// Set Enable Interrupt
	
	// TIMER 1 INIT
	TCCR1B = 0 << CS12 | 0 << CS11 | 1 << CS10;
	TIMSK |= 1 << TOIE1;			// OverFlow enable
	sei();							// Set Enable Interrupt
}


void game()
{
	//player számok bekérése:	annak megfelel?en a játékmenet beállítása
	//elindulás
	while(gameplay)
	{
		//kör++;
		//dobás gomb lenyomása:	random számot kapok
		//várakozás (el?ben játszás. (hazudik vagy sem))
		//megfelel? gombok lenyomása attól függ?en hogy veszített e életet vagy sem.
		//ha nem veszített akkor health aktuális playernek nem változik de a player + 1 nek health -= 1
		//ha a valakinek a healthje 0 akkor kiesett és az a player már nem számít bele a következ? körben
		//következ? gomb lenyomása:	másik playerre váltás	player++;
		//ha player > mint a defPlayer -> player = 0;
	}
	
}

// This function generates a random number between rndMin and rndMax	** This is not a true random number... but it works...**
int rnd_new()
{
	int dice = 0;
	
	number = rand();			// rand() -> generating a random number between 0 and 7FFFFFFF
	number &= rndMax + 1;		// cutting off digits to generate numbers between rndMin and rndMax
	
	dice = number;
	
	if (dice < rndMin)	{ dice = rndMin; }
	if (dice > rndMax)	{ dice = rndMax; }
	
	return dice;
}