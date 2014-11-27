/*
 * tapeSensor.c
 *
 * Created: 2014-11-10 14:01:47
 *  Author: Cavecanem
 */

#define F_CPU 8000000UL

#include "sensorenhet.h"


static int active_port = TAPE_SENSOR_PORT;

uint16_t led_1_value = 0;
uint16_t on_tape_value = 0;
uint16_t off_tape_value = 0;
uint16_t tape_threshold = 400;
uint8_t current_tape_sensor = 0;
uint16_t tape_data = 0;
uint16_t tape_data_done = 0;

uint16_t convertToBit(uint16_t data) {
	return data > tape_threshold;
}

// Calibrate the tape sensors to set a threshold to identify whether or not we're on tape
void calibrateTapeSensor() {
	tape_threshold = ((on_tape_value + off_tape_value) >> 1);// + 128;	// Setting the tape threshold to the average of the two tape values
}

// Set on_tape_value for the tape sensor
void setOnTape() {
	//on_tape_value = tape_data_done;
	on_tape_value = led_1_value;
	calibrateTapeSensor();							// Used in both functions so that it doesn't matter which one you call first
}

// Set off_tape_value for the tape sensor
void setOffTape() {
	//off_tape_value = tape_data_done;
	off_tape_value = led_1_value;
	calibrateTapeSensor();							// Used in both functions so that it doesn't matter which one you call first
}

ISR(ADC_vect) {
	uint16_t tape_bit = convertToBit(ADC);
	led_1_value = ADC;
	tape_data |= (tape_bit << current_tape_sensor);
	current_tape_sensor++;
	if(current_tape_sensor == 11) {
		tape_data_done = tape_data;
		tape_data = 0;
		current_tape_sensor = 0;
		PORTB = (PORTB & 0xF0) | (current_tape_sensor & 0x0F); //First clears the mux, then sets it to current_tape_sensor
		tapeDone();
			
	} else {
		PORTB = (PORTB & 0xF0) | (current_tape_sensor & 0x0F); //First clears the mux, then sets it to current_tape_sensor
		readADC(active_port);
	}
}