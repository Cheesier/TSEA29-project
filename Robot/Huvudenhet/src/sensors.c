/*
 * sensors.c
 *
 * Created: 2014-11-26 16:13:58
 *  Author: Cavecanem
 */

#include "huvudenhet.h"

// Assumes the robot stands on tape when calling this
void calibrateTapeSensor() {
	send_message_to(ADDR_SENSORENHET, 0x04, 0, 0); // Sets the on_tape value
	_delay_ms(1);
	motor_go_forward();
	_delay_ms(100); // This value needs to be tested
	motor_stop();
	send_message_to(ADDR_SENSORENHET, 0x05, 0, 0); // Sets the off_tape value	
}