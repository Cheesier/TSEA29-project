/*
 * handle_msg.c
 *
 * Created: 11/7/2014 11:36:04 AM
 *  Author: oscth887
 */

#include "message_handler.h"
#include "bluetooth.h"

void handle_message(char header, char size, char *data) {
	if (header>>6 == 0b00) { // replace 0b00 for enum (main unit)
		char type = header & 0x3F;
		switch (type) {
			case 0x01:
				//example
				break;
			default:
				// not sure how to handle this...
				break;
		}
	}
	else {
		// send to someone else
		//send_data(header, size, *data);
	}
}

void send_message(char header, char size, char *data) {
	if (header>>6 == 0b11) { // control center
		bt_send(header, size, data);
	}
	else {
		// send over SPI
	}
}