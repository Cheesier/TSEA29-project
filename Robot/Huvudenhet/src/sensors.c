/*
 * sensors.c
 *
 * Created: 2014-11-26 16:13:58
 *  Author: Cavecanem
 */

#include "huvudenhet.h"

// Assumes the robot stands on tape when calling this
void calibrateTapeSensor() {
	_delay_ms(1000);
	send_message_to(ADDR_SENSORENHET, 0x04, 0, NO_DATA); // Sets the on_tape value
	_delay_ms(1);
	motor_go_forward();
	_delay_ms(200); // This value needs to be tested
	motor_stop();
	_delay_ms(10);
	send_message_to(ADDR_SENSORENHET, 0x05, 0, NO_DATA); // Sets the off_tape value		
	lcd_set_cursor(0,2);
	printf("Calibrated!");
	_delay_ms(5000);
	lcd_clear();
}

// Fetches tapeData, it updates the tape_data variable automatically
void getTapeData() {
	send_message_to(ADDR_SENSORENHET, 0x07, 0, NO_DATA);
	_delay_us(30);
	read_message(ADDR_SENSORENHET);
	_delay_us(30);
}