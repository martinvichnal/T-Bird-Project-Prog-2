/*
* delay.c
*
* Created: 2022. 10. 15. 19:37:03
*  Author: marti
*/
#include "delay.h"



void waitMs1()
{
	_delay_ms(1);
}

void waitMs(int ms)
{
	while (ms-->0)
	{
		waitMs1();
	}
}

void waitSec(int sec)
{
	while (sec-->0)
	{
		waitMs(1000);
	}
}
