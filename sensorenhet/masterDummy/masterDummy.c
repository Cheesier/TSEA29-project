/*
 * masterDummy.c
 *
 * Created: 2014-11-06 14:07:32
 *  Author: Jonathan
 */
 
#define F_CPU 8000000
#define OVERHEAD_TIME 10

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void initSPI() {
	/* Set MOSI SCK and /SS output*/
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	/* SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void getSensorData() {
	SPDR = 0x05;
	PORTB &= ~(1<<PORTB4);
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<PORTB4);
	uint8_t noSensors = 4;
	
	_delay_us(OVERHEAD_TIME);
	
	//uint8_t *sensorData;
	//sensorData = (uint8_t*) malloc(noSensors*sizeof(uint8_t));
	
	for (int i = 0; i < noSensors; i++) {
		SPDR = 0;
		PORTB &= ~(1<<PORTB4);
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PORTB4);
	}
	
	//free(sensorData);
}

int main(void) {
	initSPI();
	
	DDRB |= (1<<0);
	DDRD &= ~(1<<2);
	//GICR |= (1<<6);
	//sei();
	while(1) {
		PORTB |= (1<<0);
		_delay_ms(100);
		PORTB &= ~(1<<0);
		_delay_ms(1000);
		getSensorData();
	}
}

ISR(SPISTC_vect) {
	PORTB |= (1<<PORTB4);
	reti(); 
}