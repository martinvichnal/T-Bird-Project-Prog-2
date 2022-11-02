/*
 * matrix.c
 *
 * Created: 2022. 10. 24. 21:47:02
 *  Author: marti
 */ 

#include "matrix.h"

// 0   1   2   3   4   5   6   7   8   9   *   # billentyuk
const unsigned char bill[12]={69, 14, 13, 11, 22, 21, 19, 38, 37, 35, 70, 67};

uint8_t matrix()
{
	uint8_t sor = 0x08;		// elso sor
	uint8_t beolvas = 0;
	uint8_t i = 0;
	
	while (sor <= 0x40)
	{
		PORTC &= 0x80;
		PORTC |= sor;			// megcimezzuk a sort
		_delay_ms(5);
		
		beolvas = (PINC & 0x7F);	// ne modositsa az RGB piros allpota.
		
		while(i < 12)
		{
			if (bill[i] == beolvas)
			{
				return i;
			}
			i++;
		}
		i = 0;
		sor<<=1;
	}
	return 12;
}