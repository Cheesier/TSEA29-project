/*
 * bluetooth.h
 *
 * Created: 11/7/2014 11:50:11 AM
 *  Author: oscth887
 */ 

void bt_init(void);
void bt_send(char header, char size, char *data);


void USARTWriteChar(char data);
char USARTReadChar(void);
	