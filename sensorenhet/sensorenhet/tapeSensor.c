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

#include "ADC.h"
#include "tapeSensor.h"

static int on_tape = 0;
static int off_tape = 0;
static int tape_threshold = 160; // (on_tape + off_tape) >> 1);// Sets the average value as threshold
static uint8_t tapeData = 0;

uint8_t getTapeData() {
	uint16_t tape_data = 0;	// The row of on/off-bits

	/*for(int i = 0; i < 11; i++) {	// Loops over all of the 11 tape sensors
		PORTB &= ~(0x0F);			// Clear the mux before setting the value
		PORTB |= i;					// Sets which tape sensor's data is converted
		uint16_t data = readADC(0);	// PORT0 is for the tape sensor

		int tape_bit = convertToBit(data);
		tape_data |= (tape_bit << i);
	}*/
	//PORTB &= ~(0x0F);
	PORTB &= ~(0x0F);
	PORTB |= 1;
	uint8_t data = readADC(0);
	PORTB &= ~(0x0F);

	//return tape_data;
	return data;
}

//TODO
int convertToBit(int data) {
	int bit = 0;
	if(data > 80) { //might work.. lol..
		data = 1;
	}
	return bit;
}

// Return tape data, used when the sensorenhet send tape data to the huvudenhet
 uint16_t returnTapeData(uint16_t tape_data) {
	return tape_data;
}


// Calibrate the tape sensors to set a threshold to identify wether or not we're on tape
void calibrateTapeSensor(char tape_pos) {

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
