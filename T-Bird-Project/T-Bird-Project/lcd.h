/*
 * lcd.h
 *
 * Created: 2022. 10. 27. 19:08:04
 *  Author: marti
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#ifndef LCD_H_
#define LCD_H_


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


void lcd_init();

void lcd_busy(void);

void lcd_cmd(uint8_t cmd);

void lcd_data(uint8_t data);

void lcd_clock();

void lcd_write(char*s);

#endif /* LCD_H_ */