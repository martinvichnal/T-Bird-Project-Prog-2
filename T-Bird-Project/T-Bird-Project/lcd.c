/*
* lcd.c
*
* Created: 2022. 10. 27. 19:07:43
*  Author: marti
*/


#include "lcd.h"

void lcd_init()
{
	DDRE |= 0xF0;
	//data7...4 out
	DDRF |= (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_EN); //RS, R/W, EN out
	//írás
	PORTF &= ~(LCD_RW);
	//R/W<-0 ->write
	PORTF &= ~(1<<LCD_RS);
	//RS <-0 ->parancs
	PORTE = 0x20;
	//0x20 parancs: Function set - Sets interface data length
	lcd_clock();
	//delay
	lcd_clock();
	//__| |__
	lcd_clock();
	//4 bites üzemmód, 8x5pixel, 2soros
	//üzemmód választás
	//nem tudjuk, hogy bekapcsolás után éppen milyenben van
	lcd_cmd(0x28);
	lcd_cmd(0x28);
	lcd_cmd(0x28);
	//lcd alaphelyzetbe
	lcd_cmd(0x02);
	//lcd törlése
	lcd_cmd(0x01);
	//kurzor villog, aláhúzás be, LCD be
	//LCD_command(0x08 | (1<<LCD_E) | (1<<LCD_CUR) | (1<<LCD_BL));
	//kurzor villog ki, aláhúzás be, LCD be
	//LCD_command(0x08 | (1<<LCD_E) | (1<<LCD_CUR) | (0<<LCD_BL));
	//kurzor villog ki, aláhúzás ki, LCD be
	lcd_cmd(0x08 | (1<<LCD_E) | (0<<LCD_CUR) | (0<<LCD_BL));
}

void lcd_busy(void)
{
	uint8_t busy;
	LCD_DATA_DDR &= ~(1<<PE7); //ott olvassuk majd a BF-et (D7-PE7)
	LCD_CMD_PORT &= ~(1<<LCD_RS); //Státusz infó
	LCD_CMD_PORT |= (1<<LCD_RW); //olvasás
	
	do{
		busy = 0;
		LCD_CMD_PORT |= (1<<LCD_EN); //EN<-1
		_delay_us(1); //felfutó
		busy=(LCD_DATA_PIN&(1<<PE7)); //átadjuk a BF értékét
		LCD_CMD_PORT &= ~(1<<LCD_EN); //EN<-0
		_delay_us(1);
		LCD_CMD_PORT |= (1<<LCD_EN); //EN<-1
		_delay_us(1);
		LCD_CMD_PORT &= ~(1<<LCD_EN); //EN<-0
		_delay_us(1);
	}while(busy);
	
	LCD_CMD_PORT &= ~(1<<LCD_RW); //R/W<-0 write
	LCD_DATA_DDR |= (1<<PE7); //PE7<-1
}


void lcd_cmd(uint8_t cmd)
{
	lcd_busy(); //Megvárjuk még felszabadul
	LCD_CMD_PORT &= ~(1<<LCD_RS); //Parancs
	LCD_CMD_PORT &= ~(1<<LCD_RW); //Küldés
	LCD_CMD_PORT &= ~(1<<LCD_EN); //EN<-0
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= (cmd&0xF0); //felsõ 4 bit küldése
	lcd_clock(); //__| |__
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= ((cmd<<4)&0xF0); //alsó 4 bit küldése
	lcd_clock(); //__| |__
}

void lcd_data(uint8_t data)
{
	lcd_busy(); //Megvárjuk még felszabadul
	LCD_CMD_PORT |= (1<<LCD_RS); //Adatregiszter
	LCD_CMD_PORT &= ~(1<<LCD_RW); //írás
	LCD_CMD_PORT &= ~(1<<LCD_EN); //EN<-0
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= (data&0xF0); //4 felsõ bit kitétele
	lcd_clock(); //__| |__
	LCD_DATA_PORT &= ~(0xF0);
	LCD_DATA_PORT |= ((data<<4)&0xF0); //alsó 4 bit kitétele
	lcd_clock(); //__| |__
}


void lcd_clock()
{
	LCD_CMD_PORT |= (1<<LCD_EN); //__|
	_delay_us(2); //
	LCD_CMD_PORT &= ~(1<<LCD_EN); // |__
	_delay_us(2);
}


void lcd_write(char*s)
{
	while (*s)
	{
		lcd_data(*s);
		s++;
	}
}