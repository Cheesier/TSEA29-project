/*
 * distanceSensor.c
 *
 * Created: 11/11/2014 10:20:00 AM
 *  Author: jonny928
 */ 

#include "sensorenhet.h"


#define TRIGGER PORTD1
#define ECHO_FRONT PIND2
#define ECHO_RIGHT PIND3
#define ECHO_BACK PIND4
#define ECHO_LEFT PIND5
#define SENSOR_INPUT PIND
#define SENSOR_OUTPUT PORTD
#define WAIT_FOR_INPUT while(!RIGHT_HIGH||!BACK_HIGH||!LEFT_HIGH||!FRONT_HIGH)

#define FRONT_HIGH (SENSOR_INPUT&(1<<ECHO_FRONT))
#define RIGHT_HIGH (SENSOR_INPUT&(1<<ECHO_RIGHT))
#define BACK_HIGH (SENSOR_INPUT&(1<<ECHO_BACK))
#define LEFT_HIGH (SENSOR_INPUT&(1<<ECHO_LEFT))

#define START_TIMER TCCR2 |= (1<<CS21)
#define STOP_TIMER TCCR2 &= ~(1<<CS21)

int getDistanceVal(){
	return distance;
}



void updateDistance() {	
	sei();
	uint8_t done[SENSOR_COUNT];
	for (int i = 0; i < SENSOR_COUNT; i++) {
		done[i] = 0;
	}
	distance = 0;
	interrupted = 0;
	TCNT2 = 0;
	//Trigger sensors
	
	SENSOR_OUTPUT |= (1<<TRIGGER);
	_delay_us(10);
	SENSOR_OUTPUT &= ~(1<<TRIGGER);
	
	

	//Wait for input from sensors
	WAIT_FOR_INPUT;
	
	//Measure length of echo signal
	START_TIMER;
	while (FRONT_HIGH || RIGHT_HIGH || BACK_HIGH || LEFT_HIGH) {
		if (!interrupted && !FRONT_HIGH && !done[DISTANCE_FRONT]) {
			STOP_TIMER;
			distanceSensors[DISTANCE_FRONT] = distance;
			START_TIMER;
			done[DISTANCE_FRONT] = 1;
		}
		if (!interrupted && !RIGHT_HIGH && !done[DISTANCE_RIGHT]) {
			STOP_TIMER;
			distanceSensors[DISTANCE_RIGHT] = distance;
			START_TIMER;
			done[DISTANCE_RIGHT] = 1;
		}
		if (!interrupted && !BACK_HIGH && !done[DISTANCE_BACK]) {
			STOP_TIMER;
			distanceSensors[DISTANCE_BACK] = distance;
			START_TIMER;
			done[DISTANCE_BACK] = 1;
		}
		if (!interrupted && !LEFT_HIGH && !done[DISTANCE_LEFT]) {
			STOP_TIMER;
			distanceSensors[DISTANCE_LEFT] = distance;
			done[DISTANCE_LEFT] = 1;
			START_TIMER;
		}
	}
	STOP_TIMER;
}

uint8_t * getDistance() {
	return distanceSensors;
}

void initDistance() {
	DDRD = (1<<TRIGGER)|(0<<ECHO_FRONT) | (0<<ECHO_RIGHT) | (0<<ECHO_BACK) | (0<<ECHO_LEFT);
	
	SENSOR_OUTPUT &= ~(1<<TRIGGER);
	
	for(int i = 0; i < SENSOR_COUNT; i++) {
		distanceSensors[i] = 4;
	}
	
	TCCR2 |= (1 << WGM21);				// Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE2);				// Enable Timer2 Output Compare Interrupt
	OCR2 = 58;							// Compare count
	DDRA |= (1<<0);
}

ISR(TIMER2_COMP_vect) {
	distance++;
	PORTA |= (1<<0);
	_delay_us(10);
	PORTA &= ~(1<<0);
}