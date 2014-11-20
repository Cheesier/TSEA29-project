/*
 * CFile1.c
 *
 * Created: 2014-11-11 10:20:26
 *  Author: microo
 */

#include "SPI.h"
#include "distanceSensor.h"
#include "tapeSensor.h"

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI |= (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<SPR0);		// Enable SPI Enable interrupts
}

// Receive over SPI
char SPI_Receive(void) {
	return SPI_Transceive(0x00);
}

// Send over SPI
void SPI_Send(char dataout) {
	SPI_Transceive(dataout);
}

char SPI_Transceive(char dataout) {
	SPDR = dataout;
	//cli();
	WAIT_FOR_TRANSFER;
<<<<<<< HEAD
	return SPDR;
=======
	//sei();
	return SPDR;	
>>>>>>> 6245549884aaa0133b3d64be2ce70ab8a8ed3634
}

void sendDistanceSensors(void) {
	SPI_Send(0x04);
	SPI_Send(0x04);
	uint8_t *sensorData;
	sensorData = getDistance();
	for (int i = 0; i < SENSOR_COUNT; i++) {
		SPI_Send(sensorData[i]);
	}
}

void sendTapeSensors() {
	SPI_Send(0x03);
	SPI_Send(0x02);
<<<<<<< HEAD
	SPI_Send(getTapeData());
	SPI_Send(0xFF);
=======
	//SPI_Send(getTapeData());	
	uint8_t highByte = (uint8_t)(tape_data_done >> 8);
	uint8_t lowByte = (uint8_t)(tape_data_done);
	SPI_Send(highByte);
	SPI_Send(lowByte);
	//SPI_Send(0xFF);	
>>>>>>> 6245549884aaa0133b3d64be2ce70ab8a8ed3634
}

void receiveMessage() {				// Testing to see if it helps to have this in main-loop instead of interrupts.
	char msg = SPI_Receive();		// interrupts are turned off for SPI for now.
	char header = (msg >> 6) & 3;
	char size = SPI_Receive();
	char data;
	msg = msg & 0x3F;
	interrupted = 1;				// Maybe useful when updating distance
	if(header == 0x02) {
		switch (msg) {
			case 0x01:				// Reset gyro angle
				resetDegreesRotated();
				break;
			case 0x02:				//how much gyro rotate
				data = SPI_Receive();
				rotateDegrees(data);
				// return value here too?
				break;
			case 0x03:				// Set on tape value
				//tape_black = vals;
				break;
			case 0x04:				// Set off tape value
				//tape_floor = vals;
				break;
			case 0x05:				// Send distance data
				sendDistanceSensors();
				break;
			case 0x06:				// Send tape data
				sendTapeSensors();
				break;
			case 0x07:				// Gyro msg
				break;
			default:
				break;
		}
	}
}

void sendGyro() {
	SPI_Send(returnDegreesRotated());
}

ISR(SPISTC_vect) {	
	char msg = SPDR;
	char header = msg >> 6;
	char size = SPI_Receive();
	msg = msg & 0x3F;
	interrupted = 1;					// Maybe useful when updating distance
	if(header == 0x02) {
		switch (msg) {
			case 0x01:					// Reset gyro angle
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
}