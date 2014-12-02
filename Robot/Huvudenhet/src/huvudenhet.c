/*
 * control_center.c
 *
 * Created: 11/7/2014 12:42:03 PM
 *  Author: oscth887
 */

#include "huvudenhet.h"

int on_tape = 0;
int autonom = 1;
uint8_t distance_data_done[4];

void interrupt_init(void) {
	GICR |= (1<< INT1)|(1<<INT0);		// Enables external interrupts via PD3
	MCUCR |= (1<<ISC11) | (1<<ISC10)|(1<<ISC01) | (1<<ISC00);
}

void autonomSet (char autonomOn) {
	if (autonomOn == 0x00) {
		autonom = 0;
	} else if (autonomOn == 0x01) {
		motor_claw_close();
		_delay_ms(500);
		motor_claw_open();
		_delay_ms(500);
		autonom = 1;
	} else {
		send_message_to(ADDR_KONTROLLCENTER, 0x3F, 0, (char *)0);
	}
}


int main(void) {
	
	
	bt_init();
	spi_init();
	lcd_init();
	interrupt_init();
	motor_claw_open();
	sei();

	_delay_ms(5000);
	
	motor_set_speed(200);
	int lock = 0;
	uint8_t test = 0;
	
	//calibrateTapeSensor();

	/*for (int i = 0; i < 4; i++) {
		lcd_set_cursor(i+1, i);
		printf("row: %i", i);
	}*/
	
	/*uint8_t deg = 45;
	send_message_to(ADDR_SENSORENHET, 0x08, 1, &deg);

	motor_set_speed(128);
	motor_go_forward();*/
	//motor_rotate_right();
	/*motor_go_forward();
	
	while(1) {
		//Testing finding the object

		//getTapeData();	
		
		lcd_set_cursor(0,0);
		printf("Tape: %4x", tape_data);
		
		//motor_go_forward();
		//if(tape_data >= 0x07FF) {
		
		
		//send_message_to(ADDR_STYRENHET, 0x01, 0, 0);
		/*if (autonom == 1) {
			_delay_ms(1);
		if(on_tape == 0 && tape_data > 0) {
			on_tape = 1;
			motor_set_speed(32);
			motor_go_forward();
		}
		if(on_tape == 1 && tape_data == 0x07FF) {
			motor_stop();
			_delay_ms(2000);
			motor_claw_close();
			//currentState = STATE_START;
			break;
		}

		_delay_us(30);
	}
	_delay_ms(1000);
	motor_claw_open();
	motor_stop();*/
	
	//motor_rotate_right_degrees(90);
	while(1){
							
		for(int i = 0; i < 4; i++) {
			if (i == 1 && distance_data[1] == 8) {
				continue;
			}
			distance_data_done[i] = distance_data[i];
		}
		lcd_distance_sensors((uint8_t*)&distance_data_done);
		/*_delay_ms(10);
		if (!lock) {
			autonomSet(1);
			lock = 1;
		}
		
		if (autonom == 1) {
			interpretSensorData(distance_data_done);
			_delay_ms(30);
		} else {
			_delay_ms(1);
		}*/
		
		/*_delay_ms(2000);
		lcd_set_cursor(1, 2);
		printf("Rotating left");
		motor_rotate_left_degrees(90);
		
		_delay_ms(2000);
		lcd_set_cursor(1, 2);
		printf("Rotating right");
		motor_rotate_right_degrees(90);*/
	}
	return 0;
}
