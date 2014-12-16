/*
 * message_handler.h
 *
 * Created: 11/7/2014 12:11:28 PM
 *  Author: oscth887
 */

#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_

#define ADDR_HUVUDENHET		 0x00
#define ADDR_STYRENHET		 0x40
#define ADDR_SENSORENHET	 0x80
#define ADDR_KONTROLLCENTER	 0xC0

#define NO_DATA 0

#include "bluetooth.h"
#include "spi.h"
#include "algorithms.h"
#include "huvudenhet.h"
#include "lcd.h"


void handle_message(uint8_t header, uint8_t size, uint8_t *data);
void send_message(uint8_t header, uint8_t size, uint8_t *data);
void send_message_to(uint8_t address, uint8_t type, uint8_t size, uint8_t *data);
void read_message(uint8_t address);

#endif

