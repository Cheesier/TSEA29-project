/*
 * control_center.c
 *
 * Created: 11/7/2014 12:42:03 PM
 *  Author: oscth887
 */


int on_tape = 0;

#include "huvudenhet.h"
void interrupt_init(void) {
	GICR |= (1<< INT1);		// Enables external interrupts via PD3
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}

int main(void) {
	bt_init();
	spi_init();
	interrupt_init();
	sei();

	//spi_write(ADDR_SENSORENHET, 0x55);
	//spi_write(ADDR_STYRENHET, 0xAA);

	/*send_message(0x86, 0, NULL);
	_delay_us(100);
	read_message(ADDR_SENSORENHET);*/

	// Vänta på sensorenheten och snurra sedan lite
	//_delay_ms(2000);

	//uint8_t deg = 90;
	//send_message_to(ADDR_SENSORENHET, 0x08, 1, &deg);
	motor_set_speed(128);
	motor_go_forward();
	//motor_rotate_right();


	while(1) {
		_delay_ms(100);
		//char dt[] = {100, 50, 40, 70};
		//send_message(0xE0, 4, &dt);
		//send_message(0x86, 0, 0);
		
		//Testing finding the object
		
		/*send_message_to(ADDR_SENSORENHET, 0x07, 0, 0);
		_delay_us(30);
		read_message(ADDR_SENSORENHET);
		//send_message_to(ADDR_STYRENHET, 0x01, 0, 0);
		
		if(on_tape == 0 && tape_data > 0) {
			on_tape = 1;
			motor_set_speed(32);
			motor_go_forward();
		}
		if(on_tape == 1 && tape_data == 0x0000) {
			motor_stop();
			_delay_us(50);
			motor_claw_close();
			//currentState = STATE_START;
			break;
		}
		
		_delay_us(30);
	}
	_delay_ms(1000);
	motor_claw_open();
	while(1) {
		_delay_ms(100);
		send_message_to(ADDR_SENSORENHET, 0x07, 0, 0);
		_delay_ms(30);
		read_message(ADDR_SENSORENHET);		*/
	}

	return 0;
}