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
#include "lcd.h"

void interrupt_init(void) {
	GICR |= (1<< INT1);		// Enables external interrupts via PD3
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}

int main(void) {
	bt_init();
	spi_init();
	lcd_init();
	interrupt_init();
	sei();

	//_delay_ms(1000);

	//spi_write(ADDR_SENSORENHET, 0x55);
	//spi_write(ADDR_STYRENHET, 0xAA);

	/*send_message(0x86, 0, NULL);
	_delay_us(100);
	read_message(ADDR_SENSORENHET);*/

	// Vänta på sensorenheten och snurra sedan lite
	_delay_ms(2000);

	char deg = 10;
	send_message_to(ADDR_SENSORENHET, 0x08, 1, &deg);
	motor_set_speed(92);
	motor_rotate_right();

	while(1) {
		/*motor_rotate_left();			// Rotera till vänster
		send_message_to(ADDR_SENSORENHET, 0x08, 1, &deg);	// Rotera 90 grader
		motor_stop();
		_delay_ms(1000);
		motor_rotate_right();			// Rotera till vänster
		send_message_to(ADDR_SENSORENHET, 0x08, 1, &deg);	// Rotera 90 grader
		motor_stop();
		_delay_ms(1000);
		*/

		//_delay_ms(100);
		/*motor_claw_close();
		_delay_ms(1000);
		motor_claw_open();*/

		//_delay_ms(100);
		//char dt[] = {100, 50, 40, 70};
		//send_message(0xE0, 4, &dt);
		//send_message(0x86, 0, 0);
		//_delay_us(30);
		//read_message(ADDR_SENSORENHET);



	}

	return 0;
}