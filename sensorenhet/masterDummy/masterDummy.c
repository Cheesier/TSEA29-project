/*
 * masterDummy.c
 *
 * Created: 2014-11-06 14:07:32
 *  Author: Jonathan
 */
 
#define F_CPU 8000000UL
#define OVERHEAD_TIME 50

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
	SPDR = 0x85;
	PORTB &= ~(1<<PORTB4);
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<PORTB4);
	
	_delay_us(OVERHEAD_TIME);	
	
	for (int i = 0; i < 4; i++) {
		SPDR = 0;
		PORTB &= ~(1<<PORTB4);
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PORTB4);
		_delay_us(20);
	}
}

void getTapeData() {
	SPDR = 0x86;
	PORTB &= ~(1<<PORTB4);
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<PORTB4);
	
	//_delay_us(OVERHEAD_TIME);
	_delay_us(150);
	
	for(int i = 0; i < 2; i++) {
		SPDR = 0;
		PORTB &= ~(1<<PORTB4);
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PORTB4);
	}
	
	
	
}

int main(void) {
	initSPI();
	
	//DDRB |= (1<<0);
	//DDRD &= ~(1<<2);
	//GICR |= (1<<6);
	//sei();
	while(1) {
		getSensorData();
		_delay_ms(1000);
	}
	/*while(1) {
		PORTB |= (1<<0);
		_delay_ms(100);
		PORTB &= ~(1<<0);
		_delay_ms(1000);
		getSensorData();
	}*/
}