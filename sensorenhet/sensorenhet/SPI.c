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
	DDR_SPI |= (1<<SPI_MISO);					// Set MISO output
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
	WAIT_FOR_TRANSFER;	
	return SPDR;
}

void sendMessage(uint8_t header, uint8_t size, uint8_t payload[]) {
	SPI_Send(header);
	SPI_Send(size);
	for(int i = 0; i < size; i++) {
		SPI_Send(payload[i]);
	}
}

void sendDistanceSensors(void) {
	SPI_Send(0x04);
	SPI_Send(0x04);
	for (int i = 0; i < SENSOR_COUNT; i++) {
		SPI_Send(distanceSensors[i]);
	}
}

// Sends the most updated tape data to the huvudenhet
void sendTapeSensors() {
	SPI_Send(0x03);
	SPI_Send(0x02);
	uint8_t highByte = (uint8_t)(tape_data_done >> 8);
	uint8_t lowByte = (uint8_t)(tape_data_done);
	SPI_Send(highByte);
	SPI_Send(lowByte);	
}

void sendGyro() {
	SPI_Send(returnDegreesRotated());
}

ISR(SPISTC_vect) {
	cli();
	char msg = SPDR;
	char header = msg >> 6;
	char size = SPI_Receive();
	msg = msg & 0x3F;
	interrupted = 1;					// Maybe useful when updating distance
	uint8_t data;
	char unknownMessage[size];
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
			case 0x08:
				data = SPI_Receive();				
				rotateDegrees(data);				
				break;
			default:	// Fetch the message anyway
			for(int i = 0; i < size; i++) {
				unknownMessage[i] = SPI_Receive();
			}
			errorMessage(size, &unknownMessage);
			break;
		}
	}
	else {			// In case of unexpected header, send an error message
		for(int i = 0; i < size; i++) {
			unknownMessage[i] = SPI_Receive();
		}
		headerError(header, size, &unknownMessage);
	}
	sei();
}

// Send back unknown messages to the control center
//TODO: Not any data
void errorMessage(int size, char *unknownMessage) {
	SPI_Send(0x3F);
	SPI_Send(size);
	for(int i = 0; i < size; i++) {
		SPI_Send(unknownMessage[i]);
		//SPI_Send((char*)(*(unknownMessage+i)));
	}
}

// Send a message back to the control center if there's an header error
//TODO: Not any data
void headerError(int header, int size, char *unknownMessage) {
	SPI_Send(0x3F);
	SPI_Send(size+1);
	SPI_Send(header);
	for(int i = 0; i < size; i++) {
		SPI_Send(unknownMessage[i]);
		//SPI_Send((char*)(*(unknownMessage+1)));
	}
	return;
}