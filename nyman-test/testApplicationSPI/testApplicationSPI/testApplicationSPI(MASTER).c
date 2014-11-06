/*
 * testApplicationSPI.c
 *
 * Created: 2014-11-04 17:04:17
 *  Author: Jonathan
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


void initSPI()
{
	/* Set MOSI SCK and /SS output*/
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	/* SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	SPDR = 0;
}

void getSensorData()
{
	uint8_t i = 1;
	SPDR = (1<<7)|(1<<6)|(0<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(1<<0);
	PORTB &= ~(1<<PORTB4);
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<PORTB4);
	
	uint8_t noSensors = SPDR;
	for (; i <= noSensors; i++)
	{
		SPDR = i;
		PORTB &= ~(1<<PORTB4);
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PORTB4);
	}
}

int main(void)
{
	initSPI();
    while(1)
    {
		_delay_ms(1000);
		getSensorData();
    }
}