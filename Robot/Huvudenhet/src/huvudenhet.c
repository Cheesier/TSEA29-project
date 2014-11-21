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
#include <avr/interrupt.h>
#include <util/delay.h>
#include "motor.h"

int main(void) {
	bt_init();
	spi_init();
	sei();
	
	//_delay_ms(1000);
	
	//spi_write(ADDR_SENSORENHET, 0x55);
	//spi_write(ADDR_STYRENHET, 0xAA);

	/*send_message(0x86, 0, NULL);
	_delay_us(100);
	read_message(ADDR_SENSORENHET);*/
	
	while(1) {
		
		_delay_ms(100);
		/*motor_claw_close();
		_delay_ms(1000);
		motor_claw_open();*/
		
		send_message(0x86, 0, 0);
		_delay_us(30);
		read_message(ADDR_SENSORENHET);
	}
	
	return 0;
}