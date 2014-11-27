/*
 * lcd.c
 *
 * Created: 11/25/2014 2:00:21 PM
 *  Author: Oscar
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "huvudenhet.h"
#include <util/delay.h>

#define LCD_PORT PORTA
#define LCD_EN 0x80
#define LCD_RS 0x20

#define LCD_OUTPUT (DDRA = 0xFF)

void lcd_reset(void) {
	// a "standard" reset of the lcd, needs to be done to enter 4-bit mode
	LCD_PORT = 0xFF;
	_delay_ms(20);
	LCD_PORT = 0x03+LCD_EN;
	LCD_PORT = 0x03;
	_delay_ms(10);
	LCD_PORT = 0x03+LCD_EN;
	LCD_PORT = 0x03;
	_delay_ms(1);
	LCD_PORT = 0x03+LCD_EN;
	LCD_PORT = 0x03;
	_delay_ms(1);
	LCD_PORT = 0x02+LCD_EN;
	LCD_PORT = 0x02;
	_delay_ms(1);
}

void lcd_init(void) {
	// set pins as output
	LCD_OUTPUT;
	
	lcd_reset();
	
	LCD_PORT = 0x03 + LCD_EN;	
	
	lcd_write(0x28);       // 4-bit mode - 2 line - 5x7 font.
	lcd_write(0x0C);       // Display no cursor - no blink.
	lcd_write(0x06);       // Automatic Increment - No Display shift.
	lcd_write(0x80);       // Address DDRAM with 0 offset 80h.
	
}

void lcd_write(uint8_t data) {
	LCD_PORT = (((data >>4) & 0x0F)|LCD_EN|LCD_RS);
	LCD_PORT = (((data >>4) & 0x0F)|LCD_RS);
	
	LCD_PORT = ((data & 0x0F)|LCD_EN|LCD_RS);
	LCD_PORT = ((data & 0x0F)|LCD_RS);
	
	_delay_us(500);
}

void lcd_set_cursor(uint8_t x, uint8_t y) {
	
}
