/*
 * ADC.c
 *
 * Created: 2014-11-10 13:52:11
 *  Author: Cavecanem
 */
#define F_CPU 8000000UL

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ADC.h"

#define WAIT_FOR_CONVERSION while(ADCSRA & (1<<ADSC)); // The function to wait for the conversion to finish


void initADC() {
	ADMUX |= (1 << REFS0) | (1<<ADLAR); // Apply 5V on AVCC, ADLAR to right align, only for testing
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // ADC Enabled, Prescaler of 64
}

uint8_t readADC(uint8_t port) {
	port &= 0x01; // Makes sure we only read port 1 or 0, the gyro is port 1, the tape sensor is port 0

	ADMUX = (ADMUX &= 0xF8) | port; // Clears port 0-7, to make sure there is nothing there that shouldn't be there

	ADCSRA |= (1<<ADSC); // Starts the conversion by setting ADSC to 1
	WAIT_FOR_CONVERSION; // Waits for the conversion to finish
	uint8_t data = ADCH;

	return data;
}