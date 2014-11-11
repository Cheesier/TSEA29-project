/*
 * sensorenhet.c
 *
 * Created: 2014-11-06 14:06:54
 *  Author: Jonathan
 */ 

#define F_CPU 8000000
#define noSensors 4

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "tapeSensor.h"

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
static int gyro_angle = 0;
static int tape_black = 0;
static int tape_floor = 0;
static int sens_timer_count = 0;
static int interrupted = 0;

void initSPI() {
	/* Set MISO output*/
	DDR_SPI = (1<<DDR_MISO);
	/* Enable SPI */
	SPCR = (1<<SPIE)|(1<<SPE);
}

void mesureAGA(void) {
	sens_timer_count = 0;
	interrupted = 0;
	uint8_t mask = (1<<PORTD1);
	TCNT2 = 0;
	PORTD |= (1<<PORTD2);
	_delay_us(10);
	PORTD &= ~(1<<PORTD2);
	//PORTB |= (1<<0);
	
	while(!(PIND &(1<<PIND1))){
			//PORTB |= (1<<0);
	}
	TCCR2 |= (1<<CS21);
	while((PIND &(1<<PIND1))){
		//PORTB |= (1<<0);
	}
	TCCR2 &= ~(1<<CS21);
	//PORTB &= ~(1<<0);
	if(!interrupted) {
		sensorData[0] = sens_timer_count;
	}
}

void sendAll(void) {
	for (int i = 0; i < noSensors; i++) {
		SPI_DATA_REG = sensorData[i];
		WAIT_FOR_TRANSFER;
	}
}

void initSensors() {
	for (int i = 0; i < noSensors; i++) {
		sensorData[i] = 129;
	}
	
	// Initiate the mux for the tape sensors
	DDRB |= 0x0F;
	// Initiate the distance sensors
	DDRD = (0<<PORTD1) | (1<<PORTD2);
}

void initSensorTimer() {
	TCCR2 |= (1 << WGM21);				// Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE2);				// Enable Timer2 Output Compare Interrupt
	//TIFR  |= 1<<TOV2;						// Clear TOV2/ clear pending interrupts
	OCR2 = 58;							// Compare count
	//TCCR2 |= (1<<CS21);					// no prescale and speed = systemclock
	
}

int main(void) {
	initSensorTimer();
	initSPI();
	initSensors();
	DDRB |= (1<<0);
	SPI_DATA_REG = noSensors; 
	sei();
	while(1) {
		mesureAGA();
		_delay_ms(1000);
	}
}



ISR(SPISTC_vect) {
	cli();
	interrupted = 1;
	int function = SPI_DATA_REG/* || (0<<7)|(0<<6)*/;			
	switch (function) {
		case 0x01:				//reset gyro_angle
			gyro_angle = 0;
			break;
		case 0x02:				//how much gyro rotate				
			break;
		case 0x03:				//on tape value
			//tape_black = vals;
			break;
		case 0x04:				//off tape value
			//tape_floor = vals;
			break;
		case 0x05:				//send distance data
			sendAll();
			break;
		case 0x06:				//send tape data
			break;
		case 0x07:				//gyro msg
			break;
		default:
			break;
	}
	sei();
}