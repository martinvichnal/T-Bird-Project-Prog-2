/*
 * rgb.h
 *
 * Created: 2022. 10. 24. 21:37:06
 *  Author: marti
 */ 

// Driving the RGB leds with PWM signals

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef RGB_H_
#define RGB_H_

// Turning on the led with custom RGB color combination and with Brightness value input.	Values can be between 0 and 255
// Brightness is changing dynamically with RGB values
void rgb_Show(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

// A fun Rainbow function that fades through all the Red Green Blue colors
void rgb_Rainbow();

// This is the PWM functions handler
void rgb_pwm_handling();

// This is used for the gameplay. It outputs a different colored RGB with different health values
void rgb_gameLights(uint8_t health);


#endif /* RGB_H_ */