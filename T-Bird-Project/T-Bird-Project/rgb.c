/*
* rgb.c
*
* Created: 2022. 10. 15. 19:35:51
*  Author: marti
*/

#include "rgb.h"

// Base values for RGB components
uint8_t brightness = 0;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

// PWM values for RGB
float pwm_red = 0;
float pwm_green = 0;
float pwm_blue = 0;

uint8_t pwm_counter = 0;

// enable bit for PWM.		1 - enabled
uint8_t rgb_enable = 1;


void rgb_Show(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
	float x = 0;

	if(brightness != 0)
	{
		x = (255 / (float)brightness);
		pwm_red = (float)r / x;
		pwm_green = (float)g / x;
		pwm_blue = (float)b / x;
	}

}


void rgb_pwm_handling()
{
	if (rgb_enable)
	{
		pwm_counter++;
		if (pwm_counter == 255)		{	pwm_counter = 0;	}
		
		
		// Switching the RED led with PWM
		if (pwm_red >= pwm_counter)
		{			
			PORTC |= (1<<PC7);
		}
		else
		{
			PORTC &= ~(1<<PC7);
		}
		
		// Switching the GREEN led with PWM
		if (pwm_green >= pwm_counter)
		{
			PORTE |= (1<<PE2);
		}
		else
		{
			PORTE &=~ (1<<PE2);
		}
		
		// Switching the BLUE led with PWM
		if (pwm_blue >= pwm_counter)
		{
			PORTE |= (1<<PE3);
		}
		else
		{
			PORTE &=~ (1<<PE3);
		}
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