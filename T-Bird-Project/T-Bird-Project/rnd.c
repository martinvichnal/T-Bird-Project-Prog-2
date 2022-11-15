/*
* rnd.c
*
* Created: 2022. 11. 15. 17:24:18
*  Author: marti
*/

#include "rnd.h"

uint8_t rnd = rndMin;
int number = 0;

// This function generates a random Mia number that is used for the game, ranges between 21 and 66
int rnd_miaDice(int previousDice)
{
	int dice = 0;
	int num1 = 0;
	int num2 = 0;
	uint8_t untilItsGood = 1;
	uint8_t bas = 0;
	
	while (untilItsGood)
	{
		num1 = rnd_dice();
		num2 = rnd_dice();
		
		if (num1 > num2)
		{
			dice = (num1 * 10) + num2;
		}
		else if (num1 < num2)
		{
			dice = (num2 * 10) + num1;
		}
		else
		{
			dice = (num1 * 10) + num1;
			bas = 1;
		}

		if (dice == 21)
		{
			untilItsGood = 0;
			break;
		}
		if (bas == 1)
		{
			untilItsGood = 0;
			bas = 0;
			break;
		}
		if (dice >= previousDice)
		{
			untilItsGood = 0;
			break;
		}
	}
	return dice;
}

// This function generates a random dice number (1 - 6)
int rnd_dice()
{
	int dice = 0;
	
	number = rand();
	dice = (number % rndMax) + 1;

	return dice;
}

// This function generates a random number between rndMin and rndMax
int rnd_withSides(int min, int max)
{
	int dice = 0;
	
	number = rand();
	dice = (number % rndMax) + min;

	return dice;
}