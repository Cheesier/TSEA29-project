/*
 * message_handler.h
 *
 * Created: 11/7/2014 12:11:28 PM
 *  Author: oscth887
 */ 

#define ADDR_HUVUDENHET		 0
#define ADDR_STYRENHET		 1
#define ADDR_SENSORENHET	 2
#define ADDR_KONTROLLCENTER	 3

void handle_message(char header, char size, char *data);
void send_message(char header, char size, char *data);