/*
* lcd.c
*
* Created: 2022. 10. 27. 19:07:43
*  Author: marti
*/


#include "lcd.h"

// LCD inicializalas
void lcd_init(void)
{
	DDRE |= 0xF0;
	//data7...4 out
	DDRF |= (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_EN);		//RS, R/W, EN out
	//írás
	PORTF &= ~(LCD_RW);
	//R/W<-0 ->write
	PORTF &= ~(1<<LCD_RS);
	//RS <-0 ->parancs
	PORTE = 0x20;
	//0x20 parancs: Function set - Sets interface data length
	lcd_clk();
	//delay
	lcd_clk();
	//__| |__
	lcd_clk();
	//4 bites üzemmód, 8x5pixel, 2soros
	//üzemmód választás
	//nem tudjuk, hogy bekapcsolás után éppen milyenben van
	lcd_write_cmd(0x28);
	lcd_write_cmd(0x28);
	lcd_write_cmd(0x28);
	//lcd alaphelyzetbe
	lcd_write_cmd(0x02);
	//lcd törlése
	lcd_write_cmd(0x01);
	//kurzor villog, aláhúzás be, LCD be
	//LCD_cmd(0x08 | (1<<LCD_E) | (1<<LCD_CUR) | (1<<LCD_BL));
	//kurzor villog ki, aláhúzás be, LCD be
	//LCD_cmd(0x08 | (1<<LCD_E) | (1<<LCD_CUR) | (0<<LCD_BL));
	//kurzor villog ki, aláhúzás ki, LCD be
	lcd_write_cmd(0x08 | (1<<LCD_E) | (0<<LCD_CUR) | (0<<LCD_BL));
}

// Parancs kuldes
void lcd_write_cmd(uint8_t cmd)
{
	// RS <- 0
	PORT_LCD_RS &= ~(1 << PIN_LCD_RS);
	// R/W <- 0
	PORT_LCD_RW &= ~(1 << PIN_LCD_RW);
	// 1. Felso 4 bit
	PORT_LCD_DATA &= MASK_H_LCD_DATA;
	PORT_LCD_DATA |= cmd & MASK_H_LCD_DATA;
	// E 0___|1|___0
	lcd_clk();
	// 2. Felso 4 bit
	PORT_LCD_DATA &= MASK_L_LCD_DATA;
	PORT_LCD_DATA |= cmd << MASK_L_LCD_DATA;
	// E 0___|1|___0
	lcd_clk();
	
}

// Adat kuldes
void lcd_write_data(uint8_t data)
{
	lcd_busy();								//Megvárjuk még felszabadul
	LCD_CMD_PORT |= (1<<LCD_RS);			//Adatregiszter
	LCD_CMD_PORT &= ~(1<<LCD_RW);			//írás
	LCD_CMD_PORT &= ~(1<<LCD_EN);			//EN<-0
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= (data&0xF0);			//4 felsõ bit kitétele
	lcd_clk();							//__| |__
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= ((data<<4)&0xF0);		//alsó 4 bit kitétele
	lcd_clk();
}

void lcd_busy(void)
{											//BF olvasása
	uint8_t busy;
	LCD_DATA_DDR &= ~(1<<PE7);				//ott olvassuk majd a BF-et (D7-PE7)
	LCD_CMD_PORT &= ~(1<<LCD_RS);			//Státusz infó
	LCD_CMD_PORT |= (1<<LCD_RW);			//olvasás
	
	do{
		busy = 0;
		LCD_CMD_PORT |= (1<<LCD_EN);		//EN<-1
		_delay_us(1);						//felfutó
		busy=(LCD_DATA_PIN&(1<<PE7));		//átadjuk a BF értékét
		LCD_CMD_PORT &= ~(1<<LCD_EN);		//EN<-0
		_delay_us(1);
		LCD_CMD_PORT |= (1<<LCD_EN);		//EN<-1
		_delay_us(1);
		LCD_CMD_PORT &= ~(1<<LCD_EN);		//EN<-0
		_delay_us(1);
	}while(busy);
	
	LCD_CMD_PORT &= ~(1<<LCD_RW);			//R/W<-0 write
	LCD_DATA_DDR |= (1<<PE7);				//PE7<-1
}

// E pin 0___|1|___0
void lcd_clk(void)
{
	// E <- 0	0___
	PORT_LCD_E &= ~(1 << PIN_LCD_E);
	_delay_ms(2);
	// E <- 1	|1|
	PORT_LCD_E |= (1 << PIN_LCD_E);
	_delay_ms(5);
	// E <- 0	___0
	PORT_LCD_E &= ~(1 << PIN_LCD_E);
	_delay_ms(3);
}


void lcd_Puts(char*s)
{
	while (*s)
	{
		lcd_write_data(*s);
		s++;
	}
}