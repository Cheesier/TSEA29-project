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
	if ((header & 0xC0) == ADDR_HUVUDENHET) {
		char type = header & 0x3F;
		switch (type) {
			case 0x00: // Gyro har roterat klart
				// hanter på något sätt
				break;
			case 0x01: // Står på stopplinje
				// hanter på något sätt
				break;
			case 0x02: // avståndssensor data
				send_message(0xE0, size, data);
				break;
			case 0x03: // tejpsensor data
				send_message(0xE1, size, data);
				break;
			default:
				// not sure how to handle this...
				//char error[] = "H: Invalid type";
				//send_message(0xFF, sizeof(error), &error);
				break;
		}
	}
	else {
		// send to someone else
		send_message(header, size, data);
	}
}

void send_message(char header, char size, char *data) {
	if ((header & 0xC0) == ADDR_KONTROLLCENTER) {
		bt_send(header, size, data);
	}
	else {
		spi_send(header, size, data);
	}
}

void send_message_to(char address, char type, char size, char *data) {
	send_message(address | type, size, data);
}

void read_message(char address) {
	char header = spi_read(address);
	char size = spi_read(address);
	char data[size];
	for (int i = 0; i < size; i++) {
		data[i] = spi_read(address);
	}
	handle_message(header, size, &data);
}
