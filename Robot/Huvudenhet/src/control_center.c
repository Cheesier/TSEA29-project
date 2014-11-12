/*
 * control_center.c
 *
 * Created: 11/7/2014 12:42:03 PM
 *  Author: oscth887
 */ 

#define F_CPU 7372800UL

#include "bluetooth.h"
#include "spi.h"
#include "message_handler.h"
#include <interrupt.h>
#include <util/delay.h>

int main(void) {
	bt_init();
	spi_init();
	sei();
	
	while(1) {
		/*_delay_ms(1000);
		send_message(0x4B, 0x00, NULL);
		_delay_ms(1000);
		send_message(0x4C, 0x00, NULL);
		*/
	}
	
	return 0;
}