#include <stdio.h>
#include <stdlib.h>

void rgb_Show(int r, int g, int b, int brightness);
int bit();

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
    }*/

    int asd = bit();

    return 0;
}

int bit()
{
    int testnum = 0x7FFFFFF6;	// 0x3363
    int dice = 0;

	testnum &= ~(0x7FFFFF80);
	dice = testnum;
    return dice;
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
