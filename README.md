# T-Bird-Project
 Ez a projekt a Programozás 2 a Gyakorlatban miatt jött létre.


-----------------------------------------------------
# Programming Setup



### Software
* Microchip Studio AVR Programmer

### Hardware - T-BIRD EXPBRD 4
* ATMEL AVR - Atmega128 mikrokontrolleler
* USB - soros átalakító
* Valós idejű óra (RTC - Real Time Clock, PCF8563)
* Piezzo buzzer
* Analóg hőmérséklet szenzor (LM35)
* RS-485 interfész (SN75176, belső védelemmel)
* USB és külső tápellátás lehetőség
* 5 db nyomógomb
* 8 db LED
* Integrált JTAG debugger (JTAG ICE)
* Védőbiztosíték
* Digitál - Analóg Átalakító
#### Accessory:
* HD44780 kompatibilis 16x4-es LCD kijelző
* 4db 7szegmenses kijelző
* 4x3-as mátrix billentyűzet
* RGB LED
*LM35 hőszenzor

### AVR - Atmega128 Pinout:

chip|pinout
---|---
**ATMega128**|<img width="300" src="resources/ATMega328.png">|

-----------------------------------------------------
# Links
* [AVR fuse calculator](http://www.engbedded.com/fusecalc)
* [AVR timer calculator](http://eleccelerator.com/avr-timer-calculator/)

-----------------------------------------------------
# Usefull code parts

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
