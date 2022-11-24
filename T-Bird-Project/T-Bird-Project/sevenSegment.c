/*
* sevenSegment.c
*
* Created: 2022. 10. 15. 19:32:31
*  Author: marti
*/

#include "sevenSegment.h"

uint8_t digit[4] = {0};
int j = 0;

// Setting the display with the right digit and number
void sevenSegment_PutDigit(uint8_t digit, uint8_t num)
{
	if (digit > 3)
	return;
	if (num > 9)
	return;

	PORTA = 0x80 | (digit) << 4 | num;
}

// Dividing num into individual digits, and counting their corresponded digit places
void sevenSegment_PutNumber(int num)
{
	digit[0] = num % 10;
	digit[1] = (num / 10) % 10;
	digit[2] = (num / 100) % 10;
	digit[3] = (num / 1000) % 10;
	
	j = (j + 1) % 4;
	sevenSegment_PutDigit(j, digit[j]);
}