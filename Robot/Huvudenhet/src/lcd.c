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
#include <stdio.h>

#define LCD_PORT PORTA
#define LCD_EN 0x80
#define LCD_RS 0x20

#define LCD_OUTPUT (DDRA = 0xFF)

static FILE mystdout = FDEV_SETUP_STREAM(lcd_write, NULL, _FDEV_SETUP_WRITE);

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
	//_delay_ms(30);
	
	lcd_cmd(0x28);		// 4-bit mode - 2 line - 5x8 font.
	lcd_cmd(0x0C);		// Display on - cursor off - blink off
	lcd_clear();
	lcd_cmd(0x06);		// increment mode
	
	stdout = &mystdout;
	
	//lcd_cmd(0x0C);		// Display no cursor - no blink.
	//lcd_cmd(0x06);		// Automatic Increment - No Display shift.
	//lcd_cmd(0x80);		// Address DDRAM with 0 offset 80h.
	
}

void lcd_cmd(uint8_t cmd) {
	LCD_PORT = (((cmd >>4) & 0x0F)|LCD_EN);
	LCD_PORT = (((cmd >>4) & 0x0F));
	
	LCD_PORT = ((cmd & 0x0F)|LCD_EN);
	LCD_PORT = (cmd & 0x0F);
	
	_delay_us(400);
}

void lcd_write(char data) {
	LCD_PORT = (((data >>4) & 0x0F)|LCD_EN|LCD_RS);
	LCD_PORT = (((data >>4) & 0x0F)|LCD_RS);
	
	LCD_PORT = ((data & 0x0F)|LCD_EN|LCD_RS);
	LCD_PORT = ((data & 0x0F)|LCD_RS);
	
	_delay_us(400);
}

void lcd_dec_write(uint8_t value) {
	
}

void lcd_hex_write(uint8_t value) {
	
}

void lcd_str_write(char *data) {
	while (*data)
		lcd_write(*data++);
}

void lcd_clear(void) {
	lcd_cmd(0x01);		// clear display
	_delay_ms(2);
}

void lcd_set_cursor(uint8_t x, uint8_t y) {
	uint8_t addr = 0x80; // first bit always set
	switch (y) {
		case 0:
			addr += 0;
			break;
		case 1:
			addr += 64;
			break;
		case 2:
			addr += 16;
			break;
		case 3:
			addr += 80;
			break;
	}
	lcd_cmd(addr+x);
}

void lcd_distance_sensors(uint8_t *distance_data) {
	lcd_set_cursor(12,0);
	printf("|%3i", distance_data[0]);
	lcd_set_cursor(12,1);
	printf("|%3i", distance_data[1]);
	lcd_set_cursor(12,2);
	printf("|%3i", distance_data[2]);
	lcd_set_cursor(12,3);
	printf("|%3i", distance_data[3]);
}

void lcd_state(uint8_t state_to_print) {
	lcd_set_cursor(0,0);
	switch(state_to_print) {
		case STATE_PD:
			printf("[ P-D ]");
			break;
		case STATE_GOTO_MIDDLE:
			printf("[ MID ]");
			break;
		case STATE_ROTATE:
			printf("[ ROT ]");
			break;
		case STATE_FIND_WALLS:
			printf("[ WAL ]");
			break;
		case STATE_ROTATE_RESET:
			printf("[ RRT ]");
			break;
		case STATE_FIND_OBJECT:
			printf("[ OBJ ]");
			break;
		case STATE_DONE:
			printf("[ DON ]");
			break;
		default:
			printf("[     ]");
			break;
	}
}

void lcd_section_type(uint8_t section_to_print) {
	lcd_set_cursor(0,1);
	switch(section_to_print) {
		case TYPE_DEAD_END:
			printf("[ D_E ]");
			break;
		case TYPE_TURN_LEFT:
			printf("[ LEF ]");
			break;
		case TYPE_TURN_RIGHT:
			printf("[ RIG ]");
			break;
		case TYPE_T_CROSS:
			printf("[  T  ]");
			break;
		case TYPE_T_CROSS_LEFT:
			printf("[ T_L ]");
			break;
		case TYPE_T_CROSS_RIGHT:
			printf("[ T_R ]");
			break;
		case TYPE_INTERSECTION:
			printf("[ CRO ]");
			break;
		case TYPE_CORRIDOR:
			printf("[ COR ]");
			break;
		default:
			printf("[     ]");
			break;
	}
}

void lcd_direction(uint8_t direction_to_print) {
	lcd_set_cursor(0,2);
	switch(direction_to_print) {
		case NOT_TURNED:
			printf("[ N_T ]");
			break;
		case LEFT:
			printf("[ LEF ]");
			break;
		case FORWARD:
			printf("[ FOR ]");
			break;
		case RIGHT:
			printf("[ RIG ]");
			break;
		default:
			printf("[     ]");
			break;
	}
}