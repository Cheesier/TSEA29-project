/*
 * control_center.c
 *
 * Created: 11/7/2014 12:42:03 PM
 *  Author: oscth887
 */ 

#define F_CPU 7372800UL

#include "bluetooth.h"
#include "message_handler.h"
#include <interrupt.h>

int main(void) {
	bt_init();
	sei();
	
	while(1) {
		
	}
	
	return 0;
}