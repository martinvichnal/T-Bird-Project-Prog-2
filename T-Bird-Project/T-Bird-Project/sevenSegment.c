/*
 * sevenSegment.c
 *
 * Created: 2022. 10. 15. 19:32:31
 *  Author: marti
 */ 

#include "sevenSegment.h"

uint8_t digit[4] = {0};
int j = 0;

void sevenSegment_PutDigit(uint8_t digit, uint8_t num)
{
	if (digit > 3)
	return;
	if (num > 9)
	return;

	PORTA = 0x80 | (digit) << 4 | num;
}
void sevenSegment_PutNumber(int num)
{
	// Digit valaszto:			// Helyiertekek
	digit[0] = num%10;			// egyes
	digit[1] = (num/10)%10;		// tizes
	digit[2] = (num/100)%10;	// szazas
	digit[3] = (num/1000)%10;	// ezrese
	
	j = (j + 1) % 4;			// Hany Digites
	sevenSegment_PutDigit(j, digit[j]);
}