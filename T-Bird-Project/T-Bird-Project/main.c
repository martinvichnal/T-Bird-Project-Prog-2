#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "matrix.h"
#include "rgb.h"
#include "rnd.h"
#include "sevenSegment.h"

#define numberOfPlayers 5

// Initializing ports, timers, interrupts
void init();
uint8_t counter = 0;		// Counter for Timer 1

// integer that sevenSegment_PutNumber() uses in Timer 1. /Can be change whenever/
int sevenSegmentNum = 0;

// Parameters, Function for game
void game();

int gameplay = 1;
int actRound = 0;
int stage = 0;						// this int checks if all the game stages has been played.
int currentPlayer = 0;				// Current player used for the struct
int tmpPreviousDice = 0;
uint8_t tmpDiceButtonState = 0;		// temporary variable for pressing the dice button
uint8_t tmpHealthButtonState = 0;	// temporary variable for pressing the WIN/LOSS button
uint8_t tmpNextPlayerHasLost = 0;	// temporary variable for checking if the current player has won the round

uint8_t gameDebug = 1;

// Player struct
struct playerState{
	uint8_t playerID;
	uint8_t playerHealth;
	uint8_t playerRandomDiceNum;
};


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







int main(void)
{
	init();
	lcd_init();
	
	while (1)
	{
		game();
	}
}


// Timer 0 for controlling RGB LEDs with PWM
ISR(TIMER0_OVF_vect)
{
	rgb_pwm_handling();
}


// Timer 1 mainly used for seven segment display
ISR(TIMER1_OVF_vect)
{
	sevenSegment_PutNumber(sevenSegmentNum);
	//counter++;
	//if (!counter)
	//{
	//	  PORTD ^= (1 << PB7); // flips the state of PD6
	//}
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



// Game function
void game()
{
	struct playerState player[numberOfPlayers];

	while(gameplay)
	{
		// Checking if the current player has lost in the previous round
		if (tmpNextPlayerHasLost)
		{
			tmpNextPlayerHasLost = 0;					// reseting the temp variable for further use
			player[currentPlayer].playerHealth--;		// taking away one health point
		}

		rgb_gameLights(player[currentPlayer].playerHealth);					// Showing the current health of the player with RGB LEDs

		// ------------------------------ STAGE 1 ------------------------------
		// Getting a dice number for the current player by pressing the 0. button
		if(PING & (1<<PG0) && (tmpDiceButtonState != 1))
		{
			tmpDiceButtonState = 1;											// the current player has pressed the button once
			player[currentPlayer].playerRandomDiceNum = rnd_miaDice(tmpPreviousDice);
			tmpPreviousDice = player[currentPlayer].playerRandomDiceNum;	// setting the "previous" dice number for the next round
			sevenSegmentNum = player[currentPlayer].playerRandomDiceNum;	// outputting the number to the seven segment display
			stage = 1;
			if (gameDebug)	{	led_out(stage);	}								// OOOOOOOx
		}
		
		// ------------------------------ STAGE 2 ------------------------------
		// if the current player lost: When the other players thinking the current player is lying
		if(PING & (1<<PG1) && (tmpHealthButtonState != 1) && (stage == 1))
		{
			tmpHealthButtonState = 1;
			stage = 2;
			if (gameDebug)	{	led_out(stage | 0x20);	}						// OOxOOOxO
		}
		// if the current player lost: When the other players thinking the current player is lying
		if(PING & (1<<PG2) && (tmpHealthButtonState != 1) && (stage == 1))
		{
			tmpHealthButtonState = 1;
			player[currentPlayer].playerHealth--;
			stage = 2;
			if (gameDebug)	{	led_out(stage | 0x80);	}						// OxOOOOxO
		}
		// if the current player won: Then when the next player is the current he has one less health
		if(PING & (1<<PG3) && (tmpHealthButtonState != 1) && (stage == 1))
		{
			tmpHealthButtonState = 1;
			tmpNextPlayerHasLost = 1;
			stage = 2;
			if (gameDebug)	{	led_out(stage | 0x40);	}						// xOOOOOxO
		}
		
		// ------------------------------ STAGE 3 ------------------------------
		// this is only activates when the dice has been rolled and when the current player has pressed the corresponding button for health
		if (stage == 2)
		{
			actRound++;									// next round
			currentPlayer++;							// next player

			if (currentPlayer > numberOfPlayers - 1)	// check if the dice has come around
			{
				currentPlayer = 0;
			}

			// reseting stage and all temp variables for the next round
			tmpDiceButtonState = 0;
			tmpHealthButtonState = 0;
			tmpNextPlayerHasLost = 0;
			tmpPreviousDice = 0;
			stage = 0;
		}

		if(PING & (1<<PG4) && (tmpHealthButtonState != 1))
		{
			tmpHealthButtonState = 1;
			if (gameDebug)	{	led_out(0xFF);	}								// xxxxxxxx
			gameplay = 0;
		}
	}
	if (gameDebug)	{	led_out(0x00);	}										// OOOOOOOO
	sevenSegmentNum = 0;
	gameplay = 1;
	actRound = 0;
	stage = 0;
	currentPlayer = 0;
	tmpPreviousDice = 0;
	tmpDiceButtonState = 0;
	tmpHealthButtonState = 0;
	tmpNextPlayerHasLost = 0;
}