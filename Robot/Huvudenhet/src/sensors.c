/*
 * sensors.c
 *
 * Created: 2014-11-26 16:13:58
 *  Author: Cavecanem
 */

#include "huvudenhet.h"

// Assumes the robot stands on tape when calling this
void calibrateTapeSensor() {
	send_message_to(ADDR_SENSORENHET, 0x04, 0, NO_DATA); // Sets the on_tape value
	_delay_ms(1);
	motor_go_forward();
	_delay_ms(100); // This value needs to be tested
	motor_stop();
	send_message_to(ADDR_SENSORENHET, 0x05, 0, NO_DATA); // Sets the off_tape value	
}

// Fetches tapeData, it updates the tape_data variable automatically
void getTapeData() {
	send_message_to(ADDR_SENSORENHET, 0x07, 0, NO_DATA);
	_delay_us(30);
	read_message(ADDR_SENSORENHET);
	_delay_us(30);
}