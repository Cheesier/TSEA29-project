/*
 * sensorenhet.c
 *
 * Created: 2014-11-06 14:06:54
 *  Author: Jonathan
 */

#include "sensorenhet.h"

#define START_TIMER TCCR1B |= (1 << CS10) | (1 << CS12);	// Set the prescaler to 1024
#define STOP_TIMER TCCR1B &= ~((1 << CS10) | (1 << CS12));

extern int distance;
extern int interrupted;
extern uint8_t distanceSensors[SENSOR_COUNT];

static int tapeIsDone = 0;
static int distanceMode= 0;

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

void tapeDone() {
	tapeIsDone = 1;
}

void initDistanceMode() {
	// Initialize timer 1
	TCCR1B |= (1 << WGM12);			// Set mode to CTC
	OCR1B = 469;						// This value with the 1024 prescaler result in the timer running for 60 ms
	START_TIMER;
	distanceMode = 1;
}

void distanceModeON() {
	distanceMode = 1;
	initDistanceMode();
}

void distanceModeOFF() {
	distanceMode = 0;
}

int main(void) {
	initSensors();
	SPI_Init();
	sei();
	readADC(0);
	initDistanceMode();
	while(1) {
		while (distanceMode){
			while (!(TIFR & (1 << OCF1B)));	// Wait for the timer to count to 60 ms
			TIFR |= (1 << OCF1A);			// Reset the timer flag
			TCNT1 = 0;
			START_TIMER;
			updateDistance();
			send_REQ();
			sendDistanceSensors();
			tapeIsDone = 0;
			PORTB = (PORTB & 0xF0); // Start LED1	
			_delay_ms(1);
			readADC(TAPE_SENSOR_PORT);
			while(tapeIsDone);
			send_REQ();
			sendTapeSensors();
		}
		_delay_ms(1);
	}
	return 0;
}
