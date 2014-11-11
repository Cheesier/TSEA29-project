/*
 * sensorenhet.c
 *
 * Created: 2014-11-06 14:06:54
 *  Author: Jonathan
 */ 

#include "sensorenhet.h"

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
/* Tapesensor */
#define TAPE_SENS PORTA0
/* Gyro */
#define GYRO PORTA1

static int tape_black = 0;
static int tape_floor = 0;

void initSensors() {	
	// Initiate the mux for the tape sensors
	DDRB |= 0x0F;
	initDistance();
}

int main(void) {
	initSensors();
	SPI_Init();
	sei();
	while(1) {
		_delay_ms(1000);
		updateDistance();
	}
}