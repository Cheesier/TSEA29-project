/*
 * control_center.c
 *
 * Created: 11/7/2014 12:42:03 PM
 *  Author: oscth887
 */

#include "huvudenhet.h"
void interrupt_init(void) {
	GICR |= (1<< INT1);		// Enables external interrupts via PD3
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}
static int autonom;
void autonomSet (char autonomOn) {
	if (autonomOn == 0x00) {
		autonom = 0;
	} else if (autonomOn == 0x01) {
		motor_claw_open();
		_delay_ms(500);
		motor_claw_close();
		_delay_ms(500);
		autonom = 1;
	} else {
		send_message_to(ADDR_KONTROLLCENTER, 0x3F, 0, (char *)0);
	}
}

int main(void) {
	autonom = 0;
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

	/*uint8_t deg = 90;
	send_message_to(ADDR_SENSORENHET, 0x08, 1, &deg);
	motor_set_speed(128);
	motor_rotate_right();*/


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

		_delay_ms(500);
		/*motor_claw_close();
		_delay_ms(500);
		motor_claw_open();*/

		/*_delay_ms(100);
		//char dt[] = {100, 50, 40, 70};
		//send_message(0xE0, 4, &dt);
		send_message(0x86, 0, 0);
		_delay_us(30);
		read_message(ADDR_SENSORENHET);*/
		//send_message_to(ADDR_STYRENHET, 0x01, 0, 0);
		/*if (autonom == 1) {
			_delay_ms(1);
		} else {
			_delay_ms(1);
		}*/
	}

	return 0;
}