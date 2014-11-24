/*
 * motor.c
 *
 * Created: 11/19/2014 4:31:58 PM
 *  Author: Oscar
 */

#include "motor.h"
#include "message_handler.h"

void init_motor(void) {
	// whatever there is to do here
}

void motor_claw_close(void) {
	send_message_to(ADDR_STYRENHET, 0x0B, 0, NO_DATA);
}

void motor_claw_open(void) {
	send_message_to(ADDR_STYRENHET, 0x0C, 0, NO_DATA);
}

void motor_set_direction(char dir) {
	char data[] = {dir};
	send_message_to(ADDR_STYRENHET, 0x04, 1, (char*)&data);
}

void motor_set_speed(char speed) {
	char data[] = {speed};
	send_message_to(ADDR_STYRENHET, 0x0E, 1, (char*)&data);
}

void motor_stop(void) {
	send_message_to(ADDR_STYRENHET, 0x0D, 0, NO_DATA);
}

void motor_go_forward(void) {
	send_message_to(ADDR_STYRENHET, 0x07, 0, NO_DATA);
}

void motor_go_backward(void) {
	send_message_to(ADDR_STYRENHET, 0x08, 0, NO_DATA);
}

void motor_rotate_left(void) {
	send_message_to(ADDR_STYRENHET, 0x09, 0, NO_DATA);
}

void motor_rotate_right(void) {
	send_message_to(ADDR_STYRENHET, 0x0A, 0, NO_DATA);
}
