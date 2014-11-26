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

int req_set = 0;
static int gyroDone = 0;
int isGyroDone() {
	return gyroDone;
}

void resetGyroDone() {
	gyroDone = 0;
}

void spi_init(void) {
	/* Set MOSI SCK and /SS output*/
	DDRB |= (1<<SS_SENSOR)|(1<<SS_STYR)|(1<<DDB5)|(1<<DDB7);
	/* SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0);

	PORTB |= (1<<SS_SENSOR) | (1<<SS_STYR);
}


char spi_transceive(char address, char data) {

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

char spi_read(char address) {
	return spi_transceive(address, 0x00);
}

void spi_write(char address, char data) {
	spi_transceive(address, data);
}

void spi_send(char header, char size, char* data) {
	char addr = header & 0xC0;
	spi_write(addr, header);
	_delay_us(30);
	spi_write(addr, size);
	for (int i = 0; i < size; i++)
		spi_write(addr, *(data+i));
}


// Interrupt routine for the REQ pin TODO: Slightly unfinished
ISR(INT1_vect) {
	gyroDone = 1;
	motor_stop();
}

ISR(SPISTC_vect) {
	//char data = SPDR;
}

/*
ISR(SPISTC_vect) {
	char header = SPDR;
	char addr = header & 0xC0;
	char size;
	char data[10];

	size = spi_read(addr);
	for (int i = 0; i < size; i++) {
		data[i] = spi_read(addr);
	}

	handle_message(header, size, (char*)&data);
}
*/