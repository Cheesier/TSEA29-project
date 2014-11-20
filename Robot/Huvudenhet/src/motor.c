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

void motor_change_dir(char dir) {
	//send_message_to(ADDR_STYRENHET, 0x04, 1, )
}

void motor_claw_close(void) {
	send_message_to(ADDR_STYRENHET, 0x0B, 0, NO_DATA);
}

void motor_claw_open(void) {
	send_message_to(ADDR_STYRENHET, 0x0C, 0, NO_DATA);
}