#include <stdio.h>
#include <stdlib.h>

void brightnessDividing(int r, int g, int b, int brightness);

int main()
{
    int r = 100;
    int b = 50;
    int g = 0;
    int brightness = 99;

    for(brightness = 100; brightness > 0; brightness--)
    {
        brightnessDividing(r, g, b, brightness);
    }


    return 0;
}


void brightnessDividing(int r, int g, int b, int brightness)
{
	float x = 0;
	float newR = 0;
	float newG = 0;
	float newB = 0;

    if(brightness != 0)
    {
        x = (100 / (float)brightness);
        newR = r / x;
        newG = g / x;
        newB = b / x;
    }


    printf("Brightness: %d\n", brightness);
    printf("Divider: %f\n", x);
    printf("Base Red value: %d\t", r);
    printf("Red: %f\n", newR);
    printf("Base Green value: %d\t", g);
    printf("Green: %f\n", newG);
    printf("Base Blue value: %d\t", b);
    printf("Blue %f\n", newB);

    printf("------------------- O -------------------\n");
}
