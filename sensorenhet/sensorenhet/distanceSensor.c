/*
 * distanceSensor.c
 *
 * Created: 11/11/2014 10:20:00 AM
 *  Author: jonny928
 */ 

#include "sensorenhet.h"

#define TRIGGER PORTD1
#define ECHO_FRONT PIND2
#define ECHO_BACK PIND3
#define ECHO_LEFT PIND4
#define ECHO_RIGHT PIND5
#define SENSOR_INPUT PIND
#define SENSOR_OUTPUT PORTD
#define WAIT_FOR_INPUT while(!RIGHT_HIGH)

#define FRONT_HIGH (SENSOR_INPUT&(1<<ECHO_FRONT))
#define RIGHT_HIGH (SENSOR_INPUT&(1<<ECHO_RIGHT))
#define BACK_HIGH (SENSOR_INPUT&(1<<ECHO_BACK))
#define LEFT_HIGH (SENSOR_INPUT&(1<<ECHO_LEFT))

#define START_TIMER TCCR2 |= (1<<CS21)
#define STOP_TIMER TCCR2 &= ~(1<<CS21)


uint8_t distanceBuffer[4][3];
uint8_t distanceCircularBuffer;

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
	uint8_t done[SENSOR_COUNT];
	uint8_t was_high[SENSOR_COUNT];
	for (int i = 0; i < SENSOR_COUNT; i++) {
		done[i] = 0;
		was_high[i] = 0;
	}
	distance = 0;
	interrupted = 0;			//
	TCNT2 = 0;
	
	//Trigger sensors
	SENSOR_OUTPUT |= (1<<TRIGGER);
	_delay_us(15);
	SENSOR_OUTPUT &= ~(1<<TRIGGER);
	
	//Wait for input from sensors
    WAIT_FOR_INPUT;
	
	//Measure length of echo signal
	START_TIMER;
	while (distance<255) {
		if(FRONT_HIGH) {
			was_high[DISTANCE_FRONT] = 1;
		}
		if(BACK_HIGH) {
			was_high[DISTANCE_BACK] = 1;
		}
		if(LEFT_HIGH) {
			was_high[DISTANCE_LEFT] = 1;
		}
		if(RIGHT_HIGH) {
			was_high[DISTANCE_RIGHT] = 1;
		}
		if (!interrupted && !FRONT_HIGH && !done[DISTANCE_FRONT] && was_high[DISTANCE_FRONT]) { 
			STOP_TIMER;
			distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer] = distance;
			START_TIMER;
			done[DISTANCE_FRONT] = 1;
		}
		if (!interrupted && !RIGHT_HIGH && !done[DISTANCE_RIGHT] && was_high[DISTANCE_RIGHT]) {
			STOP_TIMER;
			distanceBuffer[DISTANCE_RIGHT][distanceCircularBuffer] = distance;
			START_TIMER;
			done[DISTANCE_RIGHT] = 1;
		}
		if (!interrupted && !BACK_HIGH && !done[DISTANCE_BACK] && was_high[DISTANCE_BACK]) {
			STOP_TIMER;
			distanceBuffer[DISTANCE_BACK][distanceCircularBuffer] = distance;
			START_TIMER;
			done[DISTANCE_BACK] = 1;
		}
		if (!interrupted && !LEFT_HIGH && !done[DISTANCE_LEFT] && was_high[DISTANCE_LEFT]) {
			STOP_TIMER;
			distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer] = distance;
			START_TIMER;
			done[DISTANCE_LEFT] = 1;
		}
	}
	STOP_TIMER;
	for(int i = 0; i < SENSOR_COUNT; i++) {
		if(!done[i]) {
			distanceBuffer[i][distanceCircularBuffer] = 255;
		}
		distanceSensors[i] = findMedian(i);
	}
	distanceCircularBuffer += 1;
	if (distanceCircularBuffer == 3)
		distanceCircularBuffer = 0;
}

void initDistance() {
	DDRD = (1<<TRIGGER)|(0<<ECHO_FRONT) | (0<<ECHO_RIGHT) | (0<<ECHO_BACK) | (0<<ECHO_LEFT);
	
	SENSOR_OUTPUT &= ~(1<<TRIGGER);
	
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
	distance++;
}