/*
 * CFile1.c
 *
 * Created: 2014-11-11 10:20:26
 *  Author: microo
 */

#include "sensorenhet.h"
#include "tapeSensor.h"

#define GET_HEAD 0
#define GET_SIZE 1
#define GET_DATA 2

#define MAX_DATA_SIZE 2

#define TEST_PIN PINC0

int currentState = GET_HEAD;
uint8_t address, type, msgSize, data_index = 0;
uint8_t data[MAX_DATA_SIZE] = {90,90};

extern int distance;
extern int interrupted;
extern uint8_t distanceSensors[SENSOR_COUNT];

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI |= (1<<SPI_MISO);					// Set MISO output
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<SPR0);		// Enable SPI Enable interrupts
	DDRD |= (1<<REQ);							// Enable the REQ port
	DDRC |= (1<<PINC0);							// test
}

// Send a pulse over the REQ pin
void send_REQ() {
	PORTD |= (1<<REQ);
	_delay_us(1);
	PORTD &= ~(1<<REQ);
}

// Receive over SPI
char SPI_Receive(void) {
	SPDR = 0x00;
	WAIT_FOR_TRANSFER;
	return SPDR;
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
	cli();
	SPI_Send(0x04);
	SPI_Send(0x04);
	for (int i = 0; i < SENSOR_COUNT; i++) {
		SPI_Send(distanceSensors[i]);
	}
	sei();
}

// Sends the most updated tape data to the huvudenhet
void sendTapeSensors() {
	cli();
	uint8_t highByte = (uint8_t)((tape_data_done&0xFF00) >> 8);
	uint8_t lowByte = (uint8_t)(tape_data_done&0x00FF);
	SPI_Send(0x03);
	SPI_Send(0x02);
	SPI_Send(highByte);
	SPI_Send(lowByte);
	sei();
}

void sendGyro() {
	SPI_Send(returnDegreesRotated());
}

void handle_sensor_message() {
	cli();
	//char data;
	switch (type) {
		case 0x02:					// Reset gyro angle
			resetDegreesRotated();
			break;
		case 0x03:					// How much gyro rotate and who was dog
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
		case 0x08:					// Gyro rotate
			distanceModeOFF();
			rotateDegrees(data[0]);
			distanceModeON();
			break;
		default:
			break;
	}
	sei();
}

ISR(SPISTC_vect) {
    uint8_t msg = SPDR;
	SPDR = 0;
	switch(currentState) {
		case(GET_HEAD):
			address = msg >> 6;
			type = msg & 0x3F;
			currentState = GET_SIZE;
			break;
		case(GET_SIZE):
			msgSize = msg;
			if(msgSize != 0) {
				currentState = GET_DATA;
			} else {
				handle_sensor_message();
				currentState = GET_HEAD;
			}
			break;
		case(GET_DATA):
			data[data_index] = msg;
			data_index++;
			if (data_index == msgSize) {
				handle_sensor_message();
				currentState = GET_HEAD;
				data_index = 0;
			}
			break;
		default:
			currentState = GET_HEAD;
			break;
	}
	SPDR = 0;
}

/*
ISR(SPISTC_vect) {
	cli();
	char msg = SPDR;
	char size = SPI_Receive();
	char header = msg >> 6;
	msg = msg & 0x3F;
	interrupted = 1;					// Maybe useful when updating distance
	uint8_t data;
	char unknownMessage[size];
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
}*/

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
}
