#include <stdio.h>
#include <stdlib.h>

void rgb_Show(int r, int g, int b, int brightness);
//void brightnessDividing(int r, int g, int b, int brightness);

float pwm_red = 0;
float pwm_green = 0;
float pwm_blue = 0;

int main()
{
    int r = 255;
    int b = 100;
    int g = 24;
    int brightness = 100;

    // PWM values for RGB

    rgb_Show(r,g,b,brightness);

    /*for(brightness = 255; brightness > 100; brightness--)
    {
        //brightnessDividing(r, g, b, brightness);

    }
    */

    return 0;
}


void rgb_Show(int r, int g, int b, int brightness)
{
	float x = 0;

	if(brightness != 0)
	{
		x = (255 / (float)brightness);
		pwm_red = (float)r / x;
		pwm_green = (float)g / x;
		pwm_blue = (float)b / x;
	}


    printf("Brightness: %d\n", brightness);
    printf("Divider: %f\n", x);
    printf("Base Red value: %d\t", r);
    printf("Red: %f\n", pwm_red);
    printf("Base Green value: %d\t", g);
    printf("Green: %f\n", pwm_green);
    printf("Base Blue value: %d\t", b);
    printf("Blue %f\n", pwm_blue);

    printf("------------------- O -------------------\n");
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
