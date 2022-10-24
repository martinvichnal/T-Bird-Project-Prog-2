/*
 * delay.h
 *
 * Created: 2022. 10. 24. 21:36:46
 *  Author: marti
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef DELAY_H_
#define DELAY_H_

void waitMs1();

void waitMs(int ms);

void waitSec(int sec);

#endif /* DELAY_H_ */