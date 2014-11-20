/*
 * message_handler.h
 *
 * Created: 11/7/2014 12:11:28 PM
 *  Author: oscth887
 */ 

#define ADDR_HUVUDENHET		 0x00
#define ADDR_STYRENHET		 0x40
#define ADDR_SENSORENHET	 0x80
#define ADDR_KONTROLLCENTER	 0xC0

#define NO_DATA 0

void handle_message(char header, char size, char *data);
void send_message(char header, char size, char *data);
void send_message_to(char address, char type, char size, char *data);
void read_message(char address);