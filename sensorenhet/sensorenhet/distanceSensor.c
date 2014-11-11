﻿/*
 * distanceSensor.c
 *
 * Created: 11/11/2014 10:20:00 AM
 *  Author: jonny928
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "distanceSensor.h"

#define F_CPU 8000000

#define TRIGGER 1
#define ECHO_FRONT 2
#define ECHO_RIGHT 3
#define ECHO_BACK 4
#define ECHO_LEFT 5
#define SENSOR_INPUT PIND
#define SENSOR_OUTPUT PORTD
#define WAIT_FOR_INPUT while(!(SENSOR_INPUT&(1<<ECHO_FRONT)))

#define FRONT_HIGH (SENSOR_INPUT&(1<<ECHO_FRONT))
#define RIGHT_HIGH (SENSOR_INPUT&(1<<ECHO_RIGHT))
#define BACK_HIGH (SENSOR_INPUT&(1<<ECHO_BACK))
#define LEFT_HIGH (SENSOR_INPUT&(1<<ECHO_LEFT))

#define START_TIMER TCCR2 |= (1<<CS21)
#define STOP_TIMER TCCR2 &= ~(1<<CS21)



void updateDistance() {
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
			distanceSensor[DISTANCE_FRONT] = distance;
			done[DISTANCE_FRONT] = 1;
		}
		if (!interrupted && !RIGHT_HIGH && !done[DISTANCE_RIGHT]) {
			distanceSensor[DISTANCE_RIGHT] = distance;
			done[DISTANCE_RIGHT] = 1;
		}
		if (!interrupted && !LEFT_HIGH && !done[DISTANCE_BACK]) {
			distanceSensor[DISTANCE_BACK] = distance;
			done[DISTANCE_BACK] = 1;
		}
		if (!interrupted && !LEFT_HIGH && !done[DISTANCE_LEFT]) {
			distanceSensor[DISTANCE_LEFT] = distance;
			done[DISTANCE_LEFT] = 1;
		}
	}
	STOP_TIMER;
}

void initDistance() {
	DDRD |= (1<<TRIGGER);
	DDRD &= ~((1<<ECHO_FRONT) | (1<<ECHO_RIGHT) | (1<<ECHO_BACK) | (1<<ECHO_LEFT));
	
	for(int i = 0; i < SENSOR_COUNT; i++) {
		distanceSensor[i] = 0;
	}
	
	TCCR2 |= (1 << WGM21);				// Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE2);				// Enable Timer2 Output Compare Interrupt
	OCR2 = 58;							// Compare count
}

ISR(TIMER2_COMP_vect) {
	distance = distance + 1;		//add timer count;
	_delay_us(10);
}