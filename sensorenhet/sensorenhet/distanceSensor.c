/*
 * distanceSensor.c
 *
 * Created: 11/11/2014 10:20:00 AM
 *  Author: jonny928
 */ 

#include "sensorenhet.h"

#define TRIGGER_FRONT PORTD6
#define TRIGGER_LEFT PORTD7
#define TRIGGER_BACK PORTC0
#define TRIGGER_RIGHT PORTC1

#define ECHO_FRONT PIND2
#define ECHO_BACK PIND3
#define ECHO_LEFT PIND4
#define ECHO_RIGHT PIND5
#define SENSOR_INPUT PIND
#define SENSOR_OUTPUT_FRONT_AND_LEFT PORTD
#define SENSOR_OUTPUT_BACK_AND_RIGHT PORTC

// Old version, may be the reason the sensor-unit is freezing.
//#define WAIT_FOR_INPUT_FRONT_AND_LEFT while((!FRONT_HIGH || !LEFT_HIGH)&&!timedOut)
//#define WAIT_FOR_INPUT_BACK_AND_RIGHT while((!BACK_HIGH || !RIGHT_HIGH)&&!timedOut)


// New version
#define WAIT_FOR_INPUT_FRONT_AND_BACK _delay_us(760)
#define WAIT_FOR_INPUT_LEFT_AND_RIGHT _delay_us(760)


#define FRONT_HIGH (SENSOR_INPUT&(1<<ECHO_FRONT))
#define RIGHT_HIGH (SENSOR_INPUT&(1<<ECHO_RIGHT))
#define BACK_HIGH (SENSOR_INPUT&(1<<ECHO_BACK))
#define LEFT_HIGH (SENSOR_INPUT&(1<<ECHO_LEFT))

#define START_TIMER TCCR2 |= (1<<CS21)
#define STOP_TIMER TCCR2 &= ~(1<<CS21)

#define FRONT_AND_BACK 0
#define LEFT_AND_RIGHT 1

uint8_t current_pair;

uint8_t distanceBuffer[4][3];
uint8_t distanceCircularBuffer;
uint8_t distanceSensors[SENSOR_COUNT];

// Timeout-fix
uint8_t timeoutMode;
uint8_t timedOut;

uint8_t findMedian(uint8_t currentSensor) {
	if (distanceBuffer[currentSensor][0] < distanceBuffer[currentSensor][1]) {
		if (distanceBuffer[currentSensor][1] < distanceBuffer[currentSensor][2]) {
			return distanceBuffer[currentSensor][1];
		} else if (distanceBuffer[currentSensor][0] < distanceBuffer[currentSensor][2]) {
			return distanceBuffer[currentSensor][2];
		} else {
			return distanceBuffer[currentSensor][0];
		}
	} else {
		if (distanceBuffer[currentSensor][0] < distanceBuffer[currentSensor][2]) {
			return distanceBuffer[currentSensor][0];
		} else if (distanceBuffer[currentSensor][1] < distanceBuffer[currentSensor][2]) {
			return distanceBuffer[currentSensor][2];
		} else {
			return distanceBuffer[currentSensor][1];
		}
	}
}

void updateDistance() {
	
	//Setup variables
	uint8_t done[SENSOR_COUNT];							// Array to check that sensors doesn't get value multiple times
	uint8_t was_high[SENSOR_COUNT];						// Array to check if sensor echo output gets high
	for (int i = 0; i < SENSOR_COUNT; i++) {			// Resets done and was_high array
		done[i] = 0;
		was_high[i] = 0;
	}
	distance = 0;										// Distance in cm
	interrupted = 0;									// Flag to check other interrupts
	TCNT2 = 0;											// Resets counter
	
	//Trigger sensors
	if (current_pair == FRONT_AND_BACK) {
		SENSOR_OUTPUT_FRONT_AND_LEFT |= (1<<TRIGGER_FRONT);						// Trigger signal for sensors
		SENSOR_OUTPUT_BACK_AND_RIGHT |= (1<<TRIGGER_BACK);
		_delay_us(15);
		SENSOR_OUTPUT_FRONT_AND_LEFT &= ~(1<<TRIGGER_FRONT);
		SENSOR_OUTPUT_BACK_AND_RIGHT &= ~(1<<TRIGGER_BACK);
		//Wait for input from sensors
		WAIT_FOR_INPUT_FRONT_AND_BACK;										// Wait for echo signal start
	} else {
		SENSOR_OUTPUT_FRONT_AND_LEFT |= (1<<TRIGGER_LEFT);
		SENSOR_OUTPUT_BACK_AND_RIGHT |= (1<<TRIGGER_RIGHT);
		_delay_us(15);
		SENSOR_OUTPUT_FRONT_AND_LEFT &= ~(1<<TRIGGER_LEFT);
		SENSOR_OUTPUT_BACK_AND_RIGHT &= ~(1<<TRIGGER_RIGHT);
		//Wait for input from sensors
		WAIT_FOR_INPUT_LEFT_AND_RIGHT;										// Wait for echo signal start
	}
	
	//Measure length of echo signal
	START_TIMER;
	while (distance<255) {								// Safecode so distance doesn't go over 255 (max for uint8_t)
		if (current_pair == FRONT_AND_BACK) {
			if(FRONT_HIGH) {
				was_high[DISTANCE_FRONT] = 1;
			}
			if(BACK_HIGH) {
				was_high[DISTANCE_BACK] = 1;
			}
			if (!interrupted && !FRONT_HIGH && !done[DISTANCE_FRONT] && was_high[DISTANCE_FRONT]) {
				STOP_TIMER;																				// Need to stop timer to use distance variable
				distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer] = distance;						// Saves distance mesured by sensor
				START_TIMER;
				done[DISTANCE_FRONT] = 1;																// Set sensor to done
			}
			if (!interrupted && !BACK_HIGH && !done[DISTANCE_BACK] && was_high[DISTANCE_BACK]) {
				STOP_TIMER;
				distanceBuffer[DISTANCE_BACK][distanceCircularBuffer] = distance;
				START_TIMER;
				done[DISTANCE_BACK] = 1;
			}
		} else {
			if(LEFT_HIGH) {
				was_high[DISTANCE_LEFT] = 1;
			}
			if(RIGHT_HIGH) {
				was_high[DISTANCE_RIGHT] = 1;
			}
			if (!interrupted && !LEFT_HIGH && !done[DISTANCE_LEFT] && was_high[DISTANCE_LEFT]) {
				STOP_TIMER;
				distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer] = distance;
				START_TIMER;
				done[DISTANCE_LEFT] = 1;
			}
			if (!interrupted && !RIGHT_HIGH && !done[DISTANCE_RIGHT] && was_high[DISTANCE_RIGHT]) {
				STOP_TIMER;
				distanceBuffer[DISTANCE_RIGHT][distanceCircularBuffer] = distance;
				START_TIMER;
				done[DISTANCE_RIGHT] = 1;
			}
		}
	}
	STOP_TIMER;
	if (current_pair == FRONT_AND_BACK) {
		if(!done[DISTANCE_FRONT]) {
			distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_FRONT] = findMedian(DISTANCE_FRONT);
		distanceSensors[DISTANCE_FRONT] = distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer];
		
		if(!done[DISTANCE_BACK]) {
			distanceBuffer[DISTANCE_BACK][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_BACK] = findMedian(DISTANCE_BACK);
		distanceSensors[DISTANCE_BACK] = distanceBuffer[DISTANCE_BACK][distanceCircularBuffer];
	} else {
		if(!done[DISTANCE_LEFT]) {
			distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_LEFT] = findMedian(DISTANCE_LEFT);
		distanceSensors[DISTANCE_LEFT] = distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer];
		
		if(!done[DISTANCE_RIGHT]) {
			distanceBuffer[DISTANCE_RIGHT][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_RIGHT] = findMedian(DISTANCE_RIGHT);
		distanceSensors[DISTANCE_RIGHT] = distanceBuffer[DISTANCE_RIGHT][distanceCircularBuffer];
	}
	
	if (current_pair == FRONT_AND_BACK) {
		current_pair = LEFT_AND_RIGHT;
	} else {
		current_pair = FRONT_AND_BACK;
	}
	distanceCircularBuffer += 1;
	if (distanceCircularBuffer == 3)
		distanceCircularBuffer = 0;
}

void initDistance() {
	DDRD = (1<<TRIGGER_LEFT)|(1<<TRIGGER_FRONT)|(0<<ECHO_FRONT) | (0<<ECHO_RIGHT) | (0<<ECHO_BACK) | (0<<ECHO_LEFT);
	DDRC |= (1<<TRIGGER_BACK)|(1<<TRIGGER_RIGHT);
	
	SENSOR_OUTPUT_FRONT_AND_LEFT &= ~((1<<TRIGGER_FRONT)|(1<<TRIGGER_LEFT));
	SENSOR_OUTPUT_BACK_AND_RIGHT &= ~((1<<TRIGGER_BACK)|(1<<TRIGGER_RIGHT));
	
	// Timeout-fix
	timeoutMode = 0;
	timedOut = 0;
	
	current_pair = FRONT_AND_LEFT;
	interrupted = 0;
	distance = 0;
	distanceCircularBuffer = 0;
	for(int i = 0; i < SENSOR_COUNT; i++) {
		distanceSensors[i] = 0;
		for (int j = 0; j < 3; j++) {
			distanceBuffer[i][j] = 0;
		}
	}
	
	TCCR2 |= (1 << WGM21);				// Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE2);				// Enable Timer2 Output Compare Interrupt
	OCR2 = 58;							// Compare count
}

ISR(TIMER2_COMP_vect) {
	if (timeoutMode)
		timedOut = 1;
	else
		distance++;				// Add distance every 58 ms
}