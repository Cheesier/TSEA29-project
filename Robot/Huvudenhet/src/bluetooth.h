/*
 * bluetooth.h
 *
 * Created: 11/7/2014 11:50:11 AM
 *  Author: oscth887
 */ 

#include <stdint.h>

void bt_init(void);
void bt_send(uint8_t header, uint8_t size, uint8_t *data);


void USARTWriteChar(uint8_t data);
char USARTReadChar(void);
	