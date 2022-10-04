// Milyen frekvencián menjen
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void init();
void sevenSegment_PutDigit(uint8_t digit, uint8_t num);
void sevenSegment_PutNumber(int num);
void rgb_Show(uint8_t r, uint8_t g, uint8_t b);
void led_Out(uint8_t leds);


void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}

uint8_t leds = 0x01;
uint8_t ido;
uint8_t digit[4] = {0};		int j = 0;

double d = 1000;

int timerNum = 0;

uint8_t brightness = 1;
uint8_t pwm_red = 0;			uint8_t h_red = 0;
uint8_t pwm_green = 0;			uint8_t h_green = 0;
uint8_t pwm_blue = 0;			uint8_t h_blue = 0;
uint8_t szam = 0;



int main(void)
{
	init();
	
	sevenSegment_PutNumber(24);
	
	rgb_Show(1, 1, 100);
	

	while (1)
	{
		//OCR0 = duty_cycle;
		//_delay_ms(15);
		//duty_cycle += 1;
		//if (duty_cycle >= 250)
		//{
		//duty_cycle = 0;
		//OCR0 = duty_cycle;
		//_delay_ms(1000);
		//}
	}
}

ISR(TIMER0_OVF_vect)
{
	h_red++;
	h_green++;
	h_blue++;
	
	if (h_red > pwm_red)
	{
		PORTC = 0x80;
		if (h_red > 100)
		h_red = 0;
	}
	else
	{
		PORTC = 0x00;
	}
	
	
	if (h_green > pwm_green)
	{
		PORTE = 1 & 0x04;
		if (h_green > 100)
		h_green = 0;
	}
	else
	{
		PORTE = 0 & 0x04;
	}
	
	
	if (h_blue > pwm_blue)
	{
		PORTE = 1 & 0x08;
		if (h_blue > 100)
		h_blue = 0;
	}
	else
	{
		PORTE = 0 & 0x08;
	}
	
	sevenSegment_PutNumber(timerNum);
	
	// Controlling the PWM
	//szam++;
	//if (szam > brightness)
	//{
	//led_Out(0x00);
	//if (szam > 100)
	//szam = 0;
	//}
	//else
	//{
	//led_Out(0xFF);
	//}
	//

	
	//led_Out(0xFF);
	if (!ido--)
	{
		// villogtatas
		//led_Out(leds);
		//leds = leds ^ 0x01;

		// pwm test
		//brightness++;
		//if (brightness > 255)
		//{
		//brightness = 1;
		//}
		
		pwm_green++;
		if (pwm_green > 100)
		{
			pwm_green = 1;
		}
		
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
	
	// PWM
	//TCCR0 = 1 << CS02 | 0 << CS01 | 0 << CS00 | 1 << WGM00;
	
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

void rgb_Show(uint8_t r, uint8_t g, uint8_t b)
{
	// RED -> C7 (0x80), GREEN -> E2 (0x04), BLUE -> E3 (0x08)
	
	pwm_red = r;
	pwm_green = g;
	pwm_blue = b;
}