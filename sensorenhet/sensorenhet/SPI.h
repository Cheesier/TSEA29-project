/*
 * IncFile1.h
 *
 * Created: 2014-11-11 10:22:18
 *  Author: microo
 */ 

#ifndef SPI_H_
#define SPI_H_


// CPU clock
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// SPI ports
#define SPI_SS PORTB4
#define SPI_MOSI PORTB5
#define SPI_MISO PORTB6
#define SPI_SCLK PORTB7

// SPI register
#define DDR_SPI DDRB

#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)));

void SPI_Init(void);

char SPI_Recive(void);
void SPI_Send(char dataout);
void receiveMessage();

#endif /* SPI_H_ */