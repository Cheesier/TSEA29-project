/*
 * control_center.c
 *
 * Created: 11/7/2014 12:42:03 PM
 *  Author: oscth887
 */

#include "huvudenhet.h"

int on_tape = 0;
int autonom = 0;
uint8_t distance_data_done[4];

uint8_t checkpoints[4];

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

void updateSensorData() {
	for(int i = 0; i < 4; i++) {
		distance_data_done[i] = distance_data[i];
	}
}

int main(void) {
	
	initPathList();
	bt_init();
	spi_init();
	lcd_init();
	interrupt_init();
	motor_claw_open();
	sei();	
	
	_delay_ms(2000);
	
	motor_set_speed(200);
	int lock = 0;
	uint8_t test = 0;	

	while(1){		
		// Checks if the calibrate button is pressed
		if(PIND & (1<<4) && !autonom) {
			calibrateTapeSensor();
		}
		
		if ((PIND & (1<<LABYRINTH_BUTTON))) {			
			calibrateTapeSensor();
			autonom = !autonom;
			while((PIND & (1<<LABYRINTH_BUTTON)));
			_delay_ms(500);
		}
							
		updateSensorData();
		lcd_distance_sensors((uint8_t*)&distance_data_done);
		lcd_tape(tape_data);		
		
		if (autonom == 1) {
			interpretSensorData(distance_data_done);
			_delay_ms(1);
		} else {
			_delay_ms(1);
		}
	}
	return 0;
}