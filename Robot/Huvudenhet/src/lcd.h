/*
 * lcd.h
 *
 * Created: 11/25/2014 2:04:34 PM
 *  Author: Oscar
 */ 

#include <inttypes.h>

/*#define LCD_RS_PIN PINA
#define LCD_RW_PIN PINA
#define LCD_EN_PIN PINA
#define LCD_D4_PIN PINA0
#define LCD_D5_PIN PINA1
#define LCD_D6_PIN PINA2
#define LCD_D7_PIN PINA3*/

void lcd_reset(void);
void lcd_init(void);
void lcd_write(uint8_t data);