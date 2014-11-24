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

static uint8_t gyro_null_value = 0;
static uint8_t degrees_rotated = 0;
uint16_t gyro_data_done = 0;

void rotateDegrees(uint8_t degrees) {
	degrees_rotated = 0;					// Reset degrees rotated so we make sure not to rotate to much
	degrees = degrees * 100;				// To compensate for the value returned by updateGyroData being 100 times bigger than it should

	while (degrees_rotated <= degrees) {	// Rotate until we reach the requested amount of degrees rotated
		updateGyroData();
	}

	send_REQ();								// Alert our huvudenhet that we're done and should stop spinning
}

// Rotate for 10 ms and update degrees_rotated
uint16_t updateGyroData() {
	uint16_t gyro_value;
	gyro_value = gyroADC; //gyro_data_done;				// Get gyro data from the ADC. Will return a value between 0 and 1023
												// the analog output from the gyro is between 0,5 and 4,5 V

	// Gyro sensitivity is 300 dgs/s
	// Translates into 6.67 dgs/mV
	// In turn translates to a sensitivity of ~0.74 degrees for each adc value
	// Sensitivity multiplied by 100 to avoid using floats

	if (gyro_value > gyro_null_value) {
		gyro_value = (gyro_value - gyro_null_value) * 74;
	}
	else {
		gyro_value = (gyro_null_value - gyro_value) * 74;
	}
	degrees_rotated += gyro_value/100;			// Divided by 100 because we measure 100 times a second

	// IMPORTANT TO REMEMBER
	// returned value is 100 times bigger than it should be

	_delay_ms(10);
	return gyro_value;
}

// Return the amount of degrees the robot have currently rotated
uint8_t returnDegreesRotated() {
	return degrees_rotated;
}

void resetDegreesRotated(){
	degrees_rotated = 0;
}

// Wait a second to make sure that the robot is not moving, that the gyro is operational (~150 ms)
// and then read the value of the gyro to get a standard value
void initGyro() {
	_delay_ms(1000);
	gyro_null_value = gyro_data_done;		// Should give us a value of approximately 512
}