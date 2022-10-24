/*
 * sevenSegment.h
 *
 * Created: 2022. 10. 24. 21:37:20
 *  Author: marti
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

void sevenSegment_PutDigit(uint8_t digit, uint8_t num);

void sevenSegment_PutNumber(int num);

#endif /* SEVENSEGMENT_H_ */