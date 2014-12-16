/*
 * SPI.c
 *
 * Created: 11/10/2014 2:54:42 PM
 *  Author: Oscar
 */

#define F_CPU 7372800UL

#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "huvudenhet.h"

// temp
#include "bluetooth.h"

#include "message_handler.h"

uint8_t gyroMode = 0;
uint8_t indent = 0;
uint8_t req_set = 0;
uint8_t gyroDone = 0;

void gyroModeON() {
	gyroMode = 1;
}

void gyroModeOFF() {
	gyroMode = 0;
}

int isGyroDone() {
	return gyroDone;
}

void resetGyroDone() {
	gyroDone = 0;
}

void setGyroDone() {
	gyroDone = 1;
}

void spi_init(void) {
	/* Set MOSI SCK and /SS output*/
	DDRB |= (1<<SS_SENSOR)|(1<<SS_STYR)|(1<<DDB5)|(1<<DDB7);
	PORTB |= (1<<SS_SENSOR) | (1<<SS_STYR);
	/* SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	DDRD &= ~(1<<PIND2);
	DDRD &= ~(1<<PIND3);
}


char spi_transceive(uint8_t address, uint8_t data) {

	if (address == ADDR_STYRENHET)
		PORTB &= ~(1<<SS_STYR);
	else
		PORTB &= ~(1<<SS_SENSOR);
	SPDR = data;
	// read data
	while(!(SPSR & (1<<SPIF)));
	
	

	PORTB |= (1<<SS_STYR) | (1<<SS_SENSOR);

	return SPDR;
}

char spi_read(uint8_t address) {
	return spi_transceive(address, 0x00);
}

void spi_write(uint8_t address, uint8_t data) {
	spi_transceive(address, data);
}

void spi_send(uint8_t header, uint8_t size, uint8_t* data) {
	uint8_t addr = header & 0xC0;
	spi_write(addr, header);
	_delay_us(30);
	spi_write(addr, size);
	for (int i = 0; i < size; i++)
		spi_write(addr, *(data+i));
	
}


// Interrupt routine for the REQ pin TODO: Slightly unfinished
ISR(INT1_vect) {
	_delay_us(30);	
	read_message(ADDR_SENSORENHET);
}

ISR(INT0_vect) {
	//middle_done = 1;
	_delay_us(50);
	read_message(ADDR_STYRENHET);
}

ISR(SPISTC_vect) {
	//char data = SPDR;
}