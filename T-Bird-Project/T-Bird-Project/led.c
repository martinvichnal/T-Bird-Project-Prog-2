/*
 * led.c
 *
 * Created: 2022. 10. 15. 19:37:41
 *  Author: marti
 */ 

#include "led.h"

uint8_t leds = 0x01;

void led_Out(uint8_t led)
{
	PORTD = (led & 0xF0);
	PORTB = ((led << 4) & 0xF0);
}