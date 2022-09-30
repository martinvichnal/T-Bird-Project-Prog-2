# Usefull code parts

### CPU Speed
```C
#define F_CPU 8000000L
```

### CPU Speed
```C
#include <avr/io.h>
#include <util/delay.h>
```

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
