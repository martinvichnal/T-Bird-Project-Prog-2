/*
 * rnd.h
 *
 * Created: 2022. 11. 15. 17:24:10
 *  Author: marti
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef RND_H_
#define RND_H_

#define rndMax 6
#define rndMin 1

int rnd_miaDice(int);
int rnd_dice();
int rnd_withSides(int , int);

#endif /* RND_H_ */