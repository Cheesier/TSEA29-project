/*
 * CFile1.c
 *
 * Created: 2014-11-11 10:20:26
 *  Author: microo
 */ 

#include "SPI.h"
#include "Styrenhet.h"

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR = (1>>SPIE);				// Enable interrupts
}

// Receive over SPI
char SPI_Receive(void) {
	WAIT_FOR_TRANSFER;				// Wait for reception to complete
	return SPDR;					// Return Data Register
}

// Send over SPI
void SPI_Send(char dataout) {
	SPDR = dataout;					// Put package in Data Register
	WAIT_FOR_TRANSFER;				// Wait for transition to complete
}

void sendDistanceSensors(void) {
	for (int i = 0; i < noSensors; i++) {
		SPI_Send(sensorData[i]);
	}
}

ISR(SPISTC_vect) {
	cli();
	char msg = SPDR;
	char header = msg >> 6;
	char size;
	msg = msg & 0x3F;
	interrupted = 1;				//Maybe usefull when updating distance 
	if(header == 0x01) {
		switch (msg) {
			case 0x01:				//reset gyro_angle
			gyro_angle = 0;
			break;
			case 0x02:				//how much gyro rotate
			break;
			case 0x03:				//on tape value
			//tape_black = vals;
			break;
			case 0x04:				//off tape value
			//tape_floor = vals;
			break;
			case 0x05:				//send distance data
			sendDistanceSensors();
			break;
			case 0x06:				//send tape data
			break;
			case 0x07:				//gyro msg
			break;
			default:
			break;
		}
	}
	sei();
}