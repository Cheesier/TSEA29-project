/*
 * gyro.c
 *
 * Created: 13/11/2014 13:17:59
 *  Author: Erik
 */

#define F_CPU 8000000UL

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ADC.h"
#include "gyro.h"

static int gyro_null_value = 0;
static int degrees_rotated = 0;

uint8_t getGyroData() {
	uint8_t gyro_data;
	gyro_data = readADC(1);				// Get gyro data from the ADC. Will return a value between 0 and 1023

	// bla bla bla boring math here
	// bla bla bla boring math here
	// bla bla bla boring math here

	return gyro_data;
}

// Return the amount of degrees the robot have currently rotated
uint8_t returnDegreesRotated() {
	return degrees_rotated;
}

void resetDegreesRotated(){
	degrees_rotated = 0;
}

// Wait a second to make sure that the robot is not moving
// and then read the value of the gyro to get a standard value
void initGyro() {
	_delay_ms(1000);
	gyro_null_value = getGyroData();
}