// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void init();

void sevenSegment_PutDigit(uint8_t digit, uint8_t num);
void sevenSegment_PutNumber(int num);

void rgb_Show(float r, float g, float b, uint8_t brightness);
void rgb_Rainbow();

void led_Out(uint8_t leds);

void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}

uint8_t leds = 0x01;
uint8_t ido;
uint8_t digit[4] = {0};		int j = 0;

int timerNum = 0;

uint8_t brightness = 50;
float pwm_red = 0;				float h_red = 0;
float pwm_green = 0;			float h_green = 0;
float pwm_blue = 0;				float h_blue = 0;



int main(void)
{
	init();
	
	uint8_t r = 100;
	uint8_t g = 0;
	uint8_t b = 0;
	
	rgb_Show(r, g, b, brightness);
	
	while (1)
	{

		brightness--;
		if (brightness <= 0)
		{
			brightness = 100;
		}
		rgb_Show(r, g, b, brightness);
		_delay_ms(10);

		//while (g < 100)
		//{
		//g++;
		//r--;
		//rgb_Show(r, g, b);
		//_delay_ms(10);
		//}
		//while (b < 100)
		//{
		//b++;
		//g--;
		//rgb_Show(r, g, b);
		//_delay_ms(10);
		//}
		//while (r < 100)
		//{
		//r++;
		//b--;
		//rgb_Show(r, g, b);
		//_delay_ms(10);
		//}
	}
}

ISR(TIMER0_OVF_vect)
{
	h_red++;
	h_green++;
	h_blue++;
	
	// Switching the RED led with PWM
	if (h_red > pwm_red)
	{
		PORTC &=~ (1<<PC7);
		if (h_red > 100)
		h_red = 0;
	}
	else { PORTC |= (1<<PC7); }

	// Switching the GREEN led with PWM
	if (h_green > pwm_green)
	{
		PORTE &=~ (1<<PE2);
		if (h_green > 100)
		h_green = 0;
	}
	else { PORTE |= (1<<PE2); }
	
	// Switching the BLUE led with PWM
	if (h_blue > pwm_blue)
	{
		PORTE &=~ (1<<PE3);
		if (h_blue > 100)
		h_blue = 0;
	}
	else { PORTE |= (1<<PE3); }
	
	
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
	
	DDRB = 0xF0;	// Led 0-3 -> 11110000
	DDRD = 0xF0;	// Led 4-7 - 11110000
	DDRG = 0x00;	// Pushbuttons K0-K4
	
	DDRC = 0x88;	// Keyboard, -> 10001000 || Red, KBD1row?
	DDRE = 0x0C;	// RGB led -> 00001100 || Green, Blue
	
	DDRA = 0xFF;	// 7 Segment display
	
	
	// Timer init:
	TCCR0 = 0 << CS02 | 1 << CS01 | 0 << CS00;
	//TCCR0 = 1 << CS01 | 1 << CS00;
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

void led_Out(uint8_t led)
{
	PORTD = (led & 0xF0);
	PORTB = ((led << 4) & 0xF0);
}

void rgb_Show(float r, float g, float b, uint8_t brightness)
{
	// RED -> C7 (0x80), GREEN -> E2 (0x04), BLUE -> E3 (0x08)
	float x = 100 / brightness;

	if(brightness != 0)
	{
		x = (100 / (float)brightness);
		pwm_red = r / x;
		pwm_green = g / x;
		pwm_blue = b / x;
	}
}

void rgb_Rainbow()
{
	uint8_t r = 100;
	uint8_t g = 0;
	uint8_t b = 0;
	
	while (g < 100)
	{
		g++;
		r--;
		rgb_Show(r, g, b, brightness);
		_delay_ms(50);
	}
	while (b < 100)
	{
		b++;
		g--;
		rgb_Show(r, g, b, brightness);
		_delay_ms(50);
	}
	while (r < 100)
	{
		r++;
		b--;
		rgb_Show(r, g, b, brightness);
		_delay_ms(50);
	}
}