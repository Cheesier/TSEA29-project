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
	uint8_t *sensorData;
	sensorData = getDistance();
	for (int i = 0; i < SENSOR_COUNT; i++) {
		SPI_Send(sensorData[i]);
	}
}

void sendTapeSensors() {
	SPI_Send(getTapeData());
}

void sendGyro() {
	SPI_Send(returnDegreesRotated());
}

ISR(SPISTC_vect) {
	//cli();
	char msg = SPDR;
	char header = msg >> 6;
	char size;
	msg = msg & 0x3F;
	interrupted = 1;					// Maybe useful when updating distance
	if(header == 0x02) {
		switch (msg) {
			case 0x01:					// Reset gyro_angle
				resetDegreesRotated();
				break;
			case 0x02:					// How much gyro rotate and who was dog
				sendGyro();
				break;
			case 0x03:					// Set on tape value
				setOnTape();
				break;
			case 0x04:					// Set off tape value
				setOffTape();
				break;
			case 0x05:					// Send distance data
				sendDistanceSensors();
				break;
			case 0x06:					// Send tape data
				sendTapeSensors();
				break;
			case 0x07:					// Gyro msg
				break;
			default:
				break;
		}
	}
	sei();
}