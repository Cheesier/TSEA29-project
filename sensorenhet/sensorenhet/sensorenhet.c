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
/*Clock crystal*/

/*REQ signal*/
#define REQ PORTD0
/* Tape sensor */
#define TAPE_SENS PORTA0
/* Gyro */
#define GYRO PORTA1

static int tape_black = 0;
static int tape_floor = 0;

void initSensors() {
	// Initiate the mux for the tape sensors

	DDRB |= 0x0F;
	PORTB &= ~(0x0F);

	// Initiate the Analog to Digital Converter
	initADC();

	// Initiate the different sensors
	initDistance();
	initGyro();
}

int main(void) {
	initSensors();
	SPI_Init();
	sei();
	//tape_data_done = 578;
	//readADC(0);
	while(1) {
		//readADC(0);
		//_delay_ms(3);
		//updateDistance();
		//receiveMessage();
		//readADC(1);
		//pollTapeData();
		updateDistance();
		_delay_ms(60);
	}
	return 0;
}
