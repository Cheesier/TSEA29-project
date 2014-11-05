/*
 * Styrenhet.c
 *
 * Created: 04/11/2014 10:46:25
 *  Author: Erik
 */
/*
 * Atmega16_Test.c
 * Created: 03/11/2014 13:13:22
 *  Author: Erik
 */

//	DDRB = 0xFF;
//		PORTB |= (1 << LED);

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 8000000

//SPI ports
#define SPI_SS PORTB4
#define SPI_MOSI PORTB5
#define SPI_MISO PORTB6
#define SPI_SCLK PORTB7

//SPI register
#define DDR_SPI DDRB

void SPI_Init(void){
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR = (1>>SPIE);				// Enable interrupts
}

char SPI_Recive(void){
	while(!(SPSR & (1<<SPIF)));		// Wait for reception to complete
	return SPDR;					// Return Data Register
}

void SPI_Send(char dataout){
	SPDR = dataout;					// Put package in Data Register
	while(!(SPSR & (1<<SPIF)));		// Wait for transition to complete
	return;
}

// Receiving and sending could be done in the same function but this seem clearer to me

int main(void)
{
  SPI_Init();						// Initiate SPI as a slaves

  while(1){
	  while(!(false)){

		// do movement related stuff
  }
}