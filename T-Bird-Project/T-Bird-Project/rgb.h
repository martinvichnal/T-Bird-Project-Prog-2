/*
 * rgb.h
 *
 * Created: 2022. 10. 24. 21:37:06
 *  Author: marti
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef RGB_H_
#define RGB_H_

void rgb_Show(float r, float g, float b, uint8_t brightness);

void rgb_Rainbow();

void rgb_pwm_handling();


#endif /* RGB_H_ */