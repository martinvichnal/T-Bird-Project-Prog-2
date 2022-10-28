/*
 * lcd.h
 *
 * Created: 2022. 10. 27. 19:08:04
 *  Author: marti
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#ifndef LCD_H_
#define LCD_H_

#define PORT_LCD_E		PORTF			// PORT
#define DDR_LCD_E		DDRF			// DDR
#define PIN_LCD_E		PF3				// BIT

#define PORT_LCD_RW		PORTF			// PORT
#define DDR_LCD_RW		DDRF			// DDR
#define PIN_LCD_RW		PF2				// BIT

#define PORT_LCD_RS		PORTF			// PORT
#define DDR_LCD_RS		DDRF			// DDR
#define PIN_LCD_RS		PF1				// BIT

#define PORT_LCD_DATA		PORTE		// PORT
#define DDR_LCD_DATA		DDRE		// DDR
#define MASK_H_LCD_DATA		0xF0
#define MASK_L_LCD_DATA		0x0F

#define LCD_CMD_DDR		(DDRF)
#define LCD_DATA_DDR	(DDRE)
#define LCD_CMD_PORT	(PORTF)
#define LCD_DATA_PORT	(PORTE)
#define LCD_DATA_PIN	(PINE)
#define LCD_RS			(PF1)
#define LCD_RW			(PF2)
#define LCD_EN			(PF3)
#define LCD_E			2 //enable
#define LCD_CUR			1 //cursor
#define LCD_BL			0 //blink



// LCD inicializalas
void lcd_init(void);

// Parancs kuldes
void lcd_write_cmd(uint8_t cmd);

// Adat kuldes
void lcd_write_data(uint8_t data);

void lcd_busy(void);

// E pin 0___|1|___0
void lcd_clk(void);

// String iras
void lcd_Puts(char*s);

#endif /* LCD_H_ */