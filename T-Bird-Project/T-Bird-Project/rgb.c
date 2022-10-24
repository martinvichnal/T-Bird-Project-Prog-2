/*
* rgb.c
*
* Created: 2022. 10. 15. 19:35:51
*  Author: marti
*/

#include "rgb.h"

// Base values for RGB components
uint8_t brightness = 255;
uint8_t r = 255;
uint8_t g = 0;
uint8_t b = 0;

// PWM values for RGB			// Counter values of PWM
float pwm_red = 0;				float h_red = 0;
float pwm_green = 0;			float h_green = 0;
float pwm_blue = 0;				float h_blue = 0;

uint8_t rgb_enable = 1;			// enable bit for PWM.		1 - enabled


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

void rgb_pwm_handling()
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
}


