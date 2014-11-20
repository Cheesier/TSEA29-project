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
//#include "tapeSensor.h"
//#include "ADC.h"

#define TAPE_SENSOR_PORT 0
#define GYRO_PORT 1
static int active_port = TAPE_SENSOR_PORT;

static int on_tape = 0;
static int off_tape = 0;
static int tape_threshold = 160; // (on_tape + off_tape) >> 1);// Sets the average value as threshold
static uint8_t tapeData = 0;
volatile static uint8_t current_tape_sensor = 0;
volatile static uint16_t tape_data = 0;
uint16_t tape_data_done = 0;

uint8_t getTapeData() {
	//uint16_t tape_data = 0;	// The row of on/off-bits

	/*for(int i = 0; i < 11; i++) {	// Loops over all of the 11 tape sensors
		PORTB &= ~(0x0F);			// Clear the mux before setting the value
		PORTB |= i;					// Sets which tape sensor's data is converted
		uint16_t data = readADC(0);	// PORT0 is for the tape sensor

		int tape_bit = convertToBit(data);
		tape_data |= (tape_bit << i);
	}*/
	//PORTB &= ~(0x0F);
	//PORTB &= ~(0x0F);
	//PORTB |= 1;
	//uint8_t data = readADC(0);
	//PORTB &= ~(0x0F);

	//return tape_data;
	return 0;
}

//TODO
int convertToBit(int data) {
	int bit = 0;
	if(data > 150) { //might work.. lol..
		bit = 1;
	}
	return bit;
}

// Return tape data, used when the sensorenhet send tape data to the huvudenhet
 uint16_t returnTapeData(uint16_t tape_data) {
	return tape_data;
}


// Calibrate the tape sensors to set a threshold to identify whether or not we're on tape
// This function expect the robot to stand on tape at the beginning
void calibrateTapeSensor() {
	// This version is not autonomic, the robot need to be physically moved for it to work
	/*setOnTape();
	_delay_ms(10000);								// Wait 10 seconds for the robot to be moved
	setOffTape();*/
	tape_threshold = ((on_tape + off_tape) >> 1);	// Setting the tape threshold to the average of the
													// tape data on and off the tape

	// TODO (maybe): A smarter version of the calibration, asks the huvudenhet to reverse the robot before it measures the second time
/*
	uint8_t tape_data = getTapeData();
	on_tape = tape_data;
	// Move the robot
	uint8_t tape_data = getTapeData();
	off_tape = tape_data;
	tape_threshold = ((on_tape + off_tape) >> 1);	// Setting the tape threshold to the average of the
													// tape data on and off the tape
*/
}

// Set on tape value for the tape sensor
void setOnTape() {
	uint8_t tape_data = getTapeData();				// Get data from the sensors
	on_tape = tape_data;
}

// Set off tape value for the tape sensor
void setOffTape() {
	uint8_t tape_data = getTapeData();						// Get data from the sensors
	off_tape = tape_data;
}

void pollTapeData() {
	//PORTB |= 2;
	//tape_data_done = 578;
	if(active_port == TAPE_SENSOR_PORT) {
		//int tape_bit = convertToBit(ADC);
		//tape_data |= (tape_bit << current_tape_sensor);
		current_tape_sensor++;
		//current_tape_sensor = 1;
		tape_data_done = ADC;//
		if(current_tape_sensor == 9) //LED 10 is dead
			current_tape_sensor = 10;
		if(current_tape_sensor == 11) {
			//tape_data_done = tape_data;
			//active_port = GYRO_PORT;
			current_tape_sensor = 0;
		}
		//PORTB &= ~(0x0F);				// Clear the mux before setting the value
		//PORTB |= current_tape_sensor;	// Sets which tape sensor's data is converted
		PORTB = (PORTB & 0xF0) | (current_tape_sensor & 0x0F);
	}
	else if(active_port == GYRO_PORT) {
		gyro_data = ADC;
		active_port = TAPE_SENSOR_PORT;
	}
	//readADC(active_port);
}

ISR(ADC_vect) {
	//PORTB |= 2;
	//tape_data_done = 578;
	if(active_port == TAPE_SENSOR_PORT) {
		//int tape_bit = convertToBit(ADC);
		//tape_data |= (tape_bit << current_tape_sensor);
		current_tape_sensor++;
		//current_tape_sensor = 1;
		tape_data_done = ADC;//
		if(current_tape_sensor == 11) {
			//tape_data_done = tape_data;
			//active_port = GYRO_PORT;
			current_tape_sensor = 0;
		}
		//PORTB &= ~(0x0F);				// Clear the mux before setting the value
		//PORTB |= current_tape_sensor;	// Sets which tape sensor's data is converted
		PORTB = (PORTB & 0xF0) | (current_tape_sensor & 0x0F);
	}
	else if(active_port == GYRO_PORT) {
		gyro_data = ADC;
		active_port = TAPE_SENSOR_PORT;
	}
	readADC(active_port);
}
