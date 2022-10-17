#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// Ports/Timer/Interrupts initialization
void init();


// ------------------- sevenSegment_ -------------------
uint8_t digit[4] = {0};		int j = 0;
int timerNum = 0;

void sevenSegment_PutDigit(uint8_t digit, uint8_t num);
void sevenSegment_PutNumber(int num);
// -----------------------------------------------------



// ------------------- rgb_ -------------------
// Base values for RGB components
uint8_t brightness = 255;
uint8_t r = 255;
uint8_t g = 0;
uint8_t b = 0;
// PWM values for RGB			// Counter values of PWM
float pwm_red = 0;				float h_red = 0;
float pwm_green = 0;			float h_green = 0;
float pwm_blue = 0;				float h_blue = 0;

uint8_t rgb_enable = 0;

void rgb_Show(float r, float g, float b, uint8_t brightness);
void rgb_Rainbow();
// --------------------------------------------



// ------------------- led_ -------------------
uint8_t leds = 0x01;

void led_Out(uint8_t leds);
// --------------------------------------------



// ------------------- pwm -------------------
uint8_t ido;
// -------------------------------------------



// ------------------- delay_ -------------------
void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}
// ----------------------------------------------


// 0   1   2   3   4   5   6   7   8   9   *   # billentyuk
uint8_t matrix(void);
const unsigned char bill[12]={69, 14, 13, 11, 22, 21, 19, 38, 37, 35, 70, 67};



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
	if (rgb_enable)
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
	}
	
	//sevenSegment_PutNumber(timerNum);
	

	if (!ido--)
	{
		// 7segmens szamlalo
		timerNum++;
		if (timerNum == 9999)
		{
			timerNum = 0;
		}


		//brightness--;
		//if (brightness <= 0)
		//{
		//brightness = 100;
		//}
		//rgb_Show(r, g, b, brightness);
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

uint8_t matrix()
{
	uint8_t sor = 0x08;		// elso sor
	uint8_t beolvas = 0;
	uint8_t i = 0;
	
	while (sor <= 0x40)
	{
		PORTC &= 0x80;
		PORTC |= sor;			// megcimezzuk a sort
		_delay_ms(5);
		
		beolvas = PINC & 0x7F;	// ne modositsa az RGB piros allpota.
		
		while(i < 12)
		{
			if (bill[i] == beolvas)
			{
				return i;
			}
			i++;
		}
		i = 0;
		sor<<=1;
	}
	return 12;
}