/*
 * sensorenhet.c
 *
 * Created: 2014-11-06 14:06:54
 *  Author: Jonathan
 */ 

#define F_CPU 8000000
#define noSensors 4

#include <avr/io.h>
#include <util/delay.h>

// SPI defines for readability
#define DDR_SPI DDRB
#define DDR_MISO DDB6
#define SPI_DATA_REG SPDR
#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)))

// Defines for pins for sensorenhet
/*MUX ports*/
#define MUX_SELECT1 PORTB0
#define MUX_SELECT2 PORTB1
#define MUX_SELECT3 PORTB2
#define MUX_SELECT4 PORTB3
/*Clockcrystal*/

/*REQ signal*/
#define REQ PORTD0
/*Distance sensors*/
#define FRONT_DIST_SENS PORTD2
#define BACK_DIST_SENS PORTD3
#define LEFT_DIST_SENS PORTD4
#define RIGHT_DIST_SENS PORTD5
/* Tapesensor */
#define TAPE_SENS PORTA0
/* Gyro */
#define GYRO PORTA1

uint8_t sensorData [noSensors];

void initSPI()
{
	/* Set MISO output*/
	DDR_SPI = (1<<DDR_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

void sendAll()
{
	int i = 0;
	SPI_DATA_REG = noSensors;
	WAIT_FOR_TRANSFER;
	
	for (; i < noSensors; i++)
	{
		SPI_DATA_REG = sensorData[i];
		WAIT_FOR_TRANSFER;
	}
}

void initSensors()
{
	for (int i = 0; i < noSensors; i++)
	{
		sensorData[i] = i;
	}
}

int main(void)
{
	initSPI();
	initSensors();
	while(1)
	{
		sendAll();
	}
}