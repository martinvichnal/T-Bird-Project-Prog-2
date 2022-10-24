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

//#define brightness	255
//#define r			255
//#define g			0
//#define b			0
//#define pwm_red		0
//#define pwm_green	0
//#define pwm_blue	0
//#define h_red		0
//#define h_green		0
//#define h_blue		0
//
//#define rgb_enable	0;

void rgb_Show(float r, float g, float b, uint8_t brightness);

void rgb_Rainbow();



#endif /* RGB_H_ */