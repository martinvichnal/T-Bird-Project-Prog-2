/*
 * led.h
 *
 * Created: 2022. 10. 24. 21:36:57
 *  Author: marti
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef LED_H_
#define LED_H_

void led_out(uint8_t leds);

#endif /* LED_H_ */