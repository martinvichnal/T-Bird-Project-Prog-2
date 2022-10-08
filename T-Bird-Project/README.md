# Usefull code parts

### CPU Speed
```C
#define F_CPU 8000000L
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


### RGB Led
```C
// RED -> C7 (0x80)
PORTC = 0x88;
_delay_ms(1000);
PORTC = 0x00;
	
// GREEN -> E2 (0x04)
PORTE = 0x04;
_delay_ms(1000);
PORTE = 0x00;
	
// BLUE -> E3 (0x08)
PORTE = 0x08;
_delay_ms(1000);
PORTE = 0x00;
```

### Bitműveletek
```C
x = y << 1	// Balra shiftelés
x = y >> 1	// Jobbra shiftelés
x ~= y		// Bitenkénti NOT
x &= y		// Bitenkénti AND
x |= y		// Bitenkénti OR
x ^= y		// Bitenkénti XOR
```
