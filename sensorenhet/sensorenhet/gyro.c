/*
 * gyro.c
 *
 * Created: 13/11/2014 13:17:59
 *  Author: Erik
 */

#define F_CPU 8000000UL

#include "sensorenhet.h"


#define START_TIMER TCCR1B |= (1 << CS10) | (1 << CS12);	// Set the prescaler to 1024
#define STOP_TIMER TCCR1B &= ~((1 << CS10) | (1 << CS12));

static int gyro_null_value = 0;
static int degrees_rotated = 0;
uint16_t gyro_data_done = 0;

void initTimer() {
	// Initialize timer 1
	TCCR1B |= (1 << WGM12);			// Set mode to CTC
	OCR1B = 77;						// This value with the 1024 prescaler result in the timer running for 10 ms
}

void rotateDegrees(int degrees) {
	initTimer();
	degrees_rotated = 0;						// Reset degrees rotated so we make sure not to rotate to much
	degrees = degrees * 100;					// To compensate for the value returned by updateGyroData being 100 times bigger than it should
	while (abs(degrees_rotated) < degrees) {	// Rotate until we reach the requested amount of degrees rotated

		updateGyroData();
	}

	send_REQ();		// Alert our huvudenhet that we're done and should stop spinning
	SPI_Send(0x01);
	SPI_Send(0x00);
}

// Rotate for 10 ms and update degrees_rotated
void updateGyroData() {
	int gyro_value;

	TCNT1 = 0;		// Make sure the timer is reset
	START_TIMER;

	gyro_value = gyroADC();						// Get gyro data from the ADC. Will return a value between 0 and 1023
												// the analog output from the gyro is between 0,5 and 4,5 V

	// Gyro sensitivity is 300 dgs/s
	// Translates into 6.67 dgs/mV
	// In turn translates to a sensitivity of ~0.74 degrees for each adc value
	// Sensitivity multiplied by 100 to avoid using floats

	gyro_value = (gyro_null_value - gyro_value) * 64;

	degrees_rotated += gyro_value/100;		// Divided by 100 because we measure 100 times a second

	// IMPORTANT TO REMEMBER
	// returned value is 100 times bigger than it should be

	// Leave function when 10 ms have passed since we started
	while (!(TIFR & (1 << OCF1B)));
	STOP_TIMER;
	TIFR |= (1 << OCF1A);	// Reset the timer flag
}

// Return the amount of degrees the robot have currently rotated
int returnDegreesRotated() {
	return degrees_rotated;
}

void resetDegreesRotated(){
	degrees_rotated = 0;
}

// Wait a second to make sure that the robot is not moving, that the gyro is operational (~150 ms)
// and then read the value of the gyro to get a standard value
void initGyro() {
	_delay_ms(1000);
	gyro_null_value = gyroADC();	// Should give us a value of approximately 512
}