/*
 * tapeSensor.c
 *
 * Created: 2014-11-10 14:01:47
 *  Author: Cavecanem
 */ 

#include "ADC.h"
#include "tapeSensor.h"

static int on_tape = 1;
static int off_tape = 0;
static int tape_threshold = (on_tape + off_tape) >> 1);	// Sets the average value as threshold

uint16_t getTapeData() {
	uint16_t tape_data = 0;	// The row of on/off-bits
	
	for(int i = 0; i < 11; i++) {	// Loops over all of the 11 tape sensors
		PORTB &= ~(0x0F);			// Clear the mux before setting the value
		PORTB |= i;					// Sets which tape sensor's data is converted
		uint16_t data = readADC(0);	// PORT0 is for the tape sensor
		
		int tape_bit = convertToBit(data);
		tape_data |= (tape_bit << i);
	}
	
	return tape_data;
}

//TODO
int convertToBit(int data) {
	int bit = 0;
	//Do some converting based on thresholds.
	return bit;
}

void sendTapeData(uint16_t tape_data) {
	//SPISend(tape_data); TODO
}

void calibrateTapeSensor(char on_tape) {
	// get sensor data
	if(ontape == 1) {
		tape_threshold = //sensor data - x;
	}
	else {
		tape_threshold = //sensor data + x;
	}
}

