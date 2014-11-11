/*
 * handle_msg.c
 *
 * Created: 11/7/2014 11:36:04 AM
 *  Author: oscth887
 */

#include "message_handler.h"
#include "bluetooth.h"
#include "spi.h"

void handle_message(char header, char size, char *data) {
	if (header>>6 == ADDR_HUVUDENHET) {
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
		send_message(header, size, data);
	}
}

void send_message(char header, char size, char *data) {
	if (header>>6 == ADDR_KONTROLLCENTER) {
		bt_send(header, size, data);
	}
	else {
		spi_send(header, size, data);
	}
}