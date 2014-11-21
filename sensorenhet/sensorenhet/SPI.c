/*
 * CFile1.c
 *
 * Created: 2014-11-11 10:20:26
 *  Author: microo
 */

#include "sensorenhet.h"
#include "SPI.h"
#include "distanceSensor.h"
#include "tapeSensor.h"
#include "gyro.h"

extern int distance;
extern int interrupted;
extern uint8_t distanceSensors[SENSOR_COUNT];

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI |= (1<<SPI_MISO);					// Set MISO output
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<SPR0);		// Enable SPI Enable interrupts
}

// Send a pulse over the REQ pin
void send_REQ() {
	DDRD |= (1<<REQ);
	_delay_us(1);
	DDRD &= ~(1<<REQ);
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
	uint8_t data;
	msg = msg & 0x3F;
	interrupted = 1;					// Maybe useful when updating distance
	if(header == 0x02) {
		switch (msg) {
			case 0x02:					// Reset gyro angle
				resetDegreesRotated();
				break;
			case 0x03:					// How much gyro rotate
				sendGyro();
				break;
			case 0x04:					// Set on tape value
				setOnTape();
				break;
			case 0x05:					// Set off tape value
				setOffTape();
				break;
			case 0x06:					// Send distance data
				sendDistanceSensors();
				break;
			case 0x07:					// Send tape data
				sendTapeSensors();
				break;
			case 0x08:					// Rotate data amount of degrees
				data = SPI_Receive();
				cli();
				rotateDegrees(data);
				break;
			default:
				break;
		}
	}
	sei();
}