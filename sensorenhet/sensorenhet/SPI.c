/*
 * CFile1.c
 *
 * Created: 2014-11-11 10:20:26
 *  Author: microo
 */ 

#include "SPI.h"
#include "distanceSensor.h"

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPIE)|(1<<SPE);		// Enable SPI Enable interrupts
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
	for (int i = 0; i < SENSOR_COUNT; i++) {
		SPI_Send(distanceSensor[i]);
	}
}

void sendTapeSensors() {
	//cli();
	SPI_Send(getTapeData());	
	//SPI_Send(0xFF);
	//sei();
}

ISR(SPISTC_vect) {
	//cli();
	char msg = SPDR;
	char header = msg >> 6;
	char size;
	msg = msg & 0x3F;
	interrupted = 1;				//Maybe useful when updating distance 
	if(header == 0x02) {
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
				sendTapeSensors();
				break;
			case 0x07:				//gyro msg
				break;
			default:
				break;
		}
	}
	//sei();
}