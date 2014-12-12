/*
 * lcd.h
 *
 * Created: 11/25/2014 2:04:34 PM
 *  Author: Oscar
 */ 


#ifndef LCD_H_
#define LCD_H_

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
void lcd_cmd(uint8_t cmd);
void lcd_clear(void);
void lcd_write(char data);
void lcd_str_write(char *data);
void lcd_set_cursor(uint8_t x, uint8_t y);
void lcd_distance_sensors(uint8_t *distance_data);
void lcd_state(uint8_t state_to_print);
void lcd_section_type(uint8_t section_to_print);
void lcd_direction(uint8_t direction_to_print);
void lcd_nodes(uint8_t amountOfNodes);
void lcd_checkpoints();
void lcd_tape(uint16_t tapeData);
void lcd_reversing();

#endif /* LCD_H_ */