/*
 * matrix.h
 *
 * Created: 2022. 10. 24. 21:46:54
 *  Author: marti
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef MATRIX_H_
#define MATRIX_H_

	
uint8_t matrix(void);


#endif /* MATRIX_H_ */