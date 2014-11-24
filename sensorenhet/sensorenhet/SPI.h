/*
 * IncFile1.h
 *
 * Created: 2014-11-11 10:22:18
 *  Author: microo
 */

#ifndef SPI_H_
#define SPI_H_


#include "sensorenhet.h"

// SPI ports
#define SPI_SS PORTB4
#define SPI_MOSI PORTB5
#define SPI_MISO PORTB6
#define SPI_SCLK PORTB7

/*REQ signal*/
// Also defined in Sensorenhet.c but that doesn't work for some reason
#define REQ PORTD0

// SPI register
#define DDR_SPI DDRB

#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)));

void SPI_Init(void);

void send_REQ();

char SPI_Receive(void);
void SPI_Send(char dataout);
char SPI_Transceive(char dataout);
void sendMessage(uint8_t header, uint8_t size, uint8_t payload[]);

void errorMessage(int size, char* unknownMessage);
void headerError(int header, int size, char* unknownMessage);

#endif /* SPI_H_ */