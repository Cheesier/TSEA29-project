/*
 * tapeSensor.c
 *
 * Created: 2014-11-10 14:01:47
 *  Author: Cavecanem
 */

#define F_CPU 8000000UL

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sensorenhet.h"

#define TAPE_SENSOR_PORT 0
#define GYRO_PORT 1
static int active_port = TAPE_SENSOR_PORT;

static int on_tape_value = 0;
static int off_tape_value = 0;
static int tape_threshold = 256;
static uint8_t current_tape_sensor = 0;
static uint16_t tape_data = 0;
uint16_t tape_data_done = 0;

int convertToBit(int data) {
	int bit = 0;
	if(data > tape_threshold) {
		bit = 1;
	}
	return bit;
}

// Calibrate the tape sensors to set a threshold to identify whether or not we're on tape
void calibrateTapeSensor() {	
	tape_threshold = ((on_tape_value + off_tape_value) >> 1);	// Setting the tape threshold to the average of the two tape values													
}

// Set on_tape_value for the tape sensor
void setOnTape() {	
	on_tape_value = tape_data;
	calibrateTapeSensor();							// Used in both functions so that it doesn't matter which one you call first
}

// Set off_tape_value for the tape sensor
void setOffTape() {	
	off_tape_value = tape_data;
	calibrateTapeSensor();							// Used in both functions so that it doesn't matter which one you call first
}

ISR(ADC_vect) {
	if(active_port == TAPE_SENSOR_PORT) {		
		int tape_bit = convertToBit(ADC);
		tape_data |= (tape_bit << current_tape_sensor);
		current_tape_sensor++;		
		if(current_tape_sensor == 9) {				//LED 10 not working
			current_tape_sensor = 10;
		}
		if(current_tape_sensor == 11) {	
			tape_data_done = tape_data;
			if((tape_data_done & (1<<10)) && (tape_data_done & (1<<8))) { // Only for use while LED 10 isn't working
				tape_data_done |= (1 << 9);
			}
			tape_data = 0;				
			active_port = GYRO_PORT;
			current_tape_sensor = 0;
		}
		PORTB = (PORTB & 0xF0) | (current_tape_sensor & 0x0F); //First clears the mux, then sets it to current_tape_sensor
	}
	else if(active_port == GYRO_PORT) {
		gyro_data_done = ADC;
		active_port = TAPE_SENSOR_PORT;
	}
	readADC(active_port);
}
