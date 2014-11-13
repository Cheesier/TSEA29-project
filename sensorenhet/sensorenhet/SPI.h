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

// SPI register
#define DDR_SPI DDRB

#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)));

static int gyro_angle = 0;
void SPI_Init(void);

char SPI_Recive(void);
void SPI_Send(char dataout);
void receiveMessage();

#endif /* SPI_H_ */