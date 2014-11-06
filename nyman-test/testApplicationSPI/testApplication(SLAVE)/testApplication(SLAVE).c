/*
 * testApplication_SLAVE_.c
 *
 * Created: 2014-11-04 17:07:11
 *  Author: Jonathan
 */ 


#define F_CPU 8000000
#define noSensors 4

#include <avr/io.h>
#include <util/delay.h>


uint8_t sensorData [noSensors];

void initSPI()
{
	/* Set MISO output*/
	DDRB = (1<<DDB6);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

void sendAll()
{
	int i = 0;
	SPDR = noSensors;
	while(!(SPSR & (1<<SPIF)));
	
	for (; i < noSensors; i++)
	{
		SPDR = sensorData[i];
		while(!(SPSR & (1<<SPIF)));
	}
}

int main(void)
{
	initSPI();
	for (int i = 0; i < noSensors; i++)
	{
		sensorData[i] = 0;
	}
    while(1)
    {
        sendAll();
    }
}