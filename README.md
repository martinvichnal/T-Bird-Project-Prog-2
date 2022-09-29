# T-Bird-Project
 Ez a projekt a Programozás 2 a Gyakorlatban miatt jött létre.

# AVR-projects

# Programming Setup
I almost always use AVRISPmkII and AVRdude (launched from a batch script) to program my chips. I virtually never use AVRStudio. I typically develop in a Windows environment, but the code (and AVRdude) works the same in Linux.


### Software
* 

### Hardware
* [AVR Programming in 64-bit Windows 7](http://www.swharden.com/wp/2013-05-07-avr-programming-in-64-bit-windows-7/) (should also work for windows 10)

## Common AVR Datasheets and Pinouts

chip|pinout|datasheets
---|---|---
**ATMega328**|<img width="300" src="resources/ATMega328.png">|[[summary](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Summary.pdf)] [[complete](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf)]
**ATTiny2313**|<img width="300" src="resources/ATTiny2313.png">|[[summary](http://www.atmel.com/Images/8246S.pdf)] [[complete](http://www.atmel.com/Images/doc8246.pdf)]|<img width="300" src="resources/ATMega328.png">
**ATTiny45**|<img width="300" src="resources/ATTiny45.png">|[[summary](http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet-Summary.pdf)] [[complete](http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf)]|<img width="300" src="resources/ATMega328.png)

# Helpful Links
* [AVR fuse calculator](http://www.engbedded.com/fusecalc)
* [AVR timer calculator](http://eleccelerator.com/avr-timer-calculator/)

## Misc Code

### Reading pins
```C
if(PIND&(1<<PD7)){doSomething();} // runs doSomething() if PD7 is HIGH
```

### Bit flipping in C
```c
PORTD|=(1<<PD6); // sets PD6 high
PORTD&=~(1<<PD6); // sets PD6 low
PORTD^=(1<<PD6); // flips the state of PD6
```

### Memory-Efficient Timers
```C
#include <util/delay.h>
void waitMs1(){_delay_ms(1);}
void waitMs(int ms){while (ms-->0){waitMs1();}}
void waitSec(int sec){while (sec-->0){waitMs(1000);}}
```
