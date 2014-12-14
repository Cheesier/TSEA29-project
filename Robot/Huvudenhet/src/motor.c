/*
 * motor.c
 *
 * Created: 11/19/2014 4:31:58 PM
 *  Author: Oscar
 */

#include "motor.h"
//#include "message_handler.h"
#include "huvudenhet.h"



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
	if(dir == DIR_REVERSE) {
		reversing = TRUE;
	}
	else {
		reversing = FALSE;
	}
	send_message_to(ADDR_STYRENHET, 0x04, 1, (char*)&data);	// 1 for forward, 0 for backwards
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

void motor_go_forward_pd(void) {
	send_message_to(ADDR_STYRENHET, 0x01, 0, NO_DATA);
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

void motor_rotate_left_degrees(uint8_t degrees) {
	if(!reversing)
		degrees += 2;
	send_message_to(ADDR_SENSORENHET, 0x08, 0x01, &degrees); // Send interrupt when we've reached degrees degrees
	gyroModeON();
	motor_rotate_left();
}

void motor_rotate_right_degrees(uint8_t degrees) {
	send_message_to(ADDR_SENSORENHET, 0x08, 0x01, &degrees); // Send interrupt when we've reached degrees degrees
	gyroModeON();
	motor_rotate_right();
}

void motor_forward_to_middle() {
	send_message_to(ADDR_STYRENHET, 0x11, 0, NO_DATA);
}

void motor_set_pd(uint8_t p, uint8_t d) {
	char data[] = {p,d};
	send_message_to(ADDR_STYRENHET, 0x06, 2, &data);
}

void motor_reset_pd() {
	char data[] = {11,40};
	send_message_to(ADDR_STYRENHET, 0x06, 2, &data);
}