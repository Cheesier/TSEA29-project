/*
 * sensorenhet.c
 *
 * Created: 2014-11-06 14:06:54
 *  Author: Jonathan
 */

#include "sensorenhet.h"

extern int distance;
extern int interrupted;
extern uint8_t distanceSensors[SENSOR_COUNT];

// SPI defines for readability
#define DDR_SPI DDRB
#define DDR_MISO DDB6

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
	readADC(0);
	while(1) {
		updateDistance();
		_delay_ms(60);
	}
	return 0;
}
