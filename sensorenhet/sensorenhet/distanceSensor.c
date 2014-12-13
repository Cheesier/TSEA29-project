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
#define WAIT_FOR_INPUT_FRONT_AND_LEFT _delay_us(760)
#define WAIT_FOR_INPUT_BACK_AND_RIGHT _delay_us(760)


#define FRONT_HIGH (SENSOR_INPUT&(1<<ECHO_FRONT))
#define RIGHT_HIGH (SENSOR_INPUT&(1<<ECHO_RIGHT))
#define BACK_HIGH (SENSOR_INPUT&(1<<ECHO_BACK))
#define LEFT_HIGH (SENSOR_INPUT&(1<<ECHO_LEFT))

#define START_TIMER TCCR2 |= (1<<CS21)
#define STOP_TIMER TCCR2 &= ~(1<<CS21)

#define FRONT_AND_LEFT 0
#define BACK_AND_RIGHT 1

uint8_t current_pair;

uint16_t distanceBuffer[4][3];
uint8_t distanceCircularBuffer;
uint16_t distanceSensors[SENSOR_COUNT];

// Timeout-fix
uint8_t timeoutMode;
uint8_t timedOut;


/************************************************************************/
/* Optical sensors - start                                              */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/


#define VALUE_AT_30 103
#define VALUE_AT_25 125
#define VALUE_AT_20 154
#define VALUE_AT_15 207
#define VALUE_AT_10 301
#define VALUE_AT_05 549
#define VALUE_AT_03 757

#define K_AT_30 2
#define K_AT_25 4
#define K_AT_20 6
#define K_AT_15 11
#define K_AT_10 19
#define K_AT_05 50
#define K_AT_03 104

uint8_t sensorADMux [SENSOR_COUNT] = {(1<<MUX1),			// ADC2
									  (1<<MUX1)|(1<<MUX0),	// ADC3
									  (1<<MUX2),			// ADC4
									  (1<<MUX2)|(1<<MUX0)};	//

uint16_t convert_to_mm(uint16_t signal) {
	if (signal <= VALUE_AT_30) {
		return 300 + (10*(VALUE_AT_30-signal)/K_AT_30);
	} else if (signal <= VALUE_AT_25) {
		return 250 + (10*(VALUE_AT_25-signal)/K_AT_25);
	} else if (signal <= VALUE_AT_20) {
		return 200 + (10*(VALUE_AT_20-signal)/K_AT_20);
	} else if (signal <= VALUE_AT_15) {
		return 150 + (10*(VALUE_AT_15-signal)/K_AT_15);
	} else if (signal <= VALUE_AT_10) {
		return 100 + (10*(VALUE_AT_10-signal)/K_AT_10);
	} else if (signal <= VALUE_AT_05) {
		return 50 + (10*(VALUE_AT_05-signal)/K_AT_05);
	} else if (signal <= VALUE_AT_03) {
		return 30 + (10*(VALUE_AT_03-signal)/K_AT_03);
	} else {
		return 0 + (10*(VALUE_AT_03-signal)/K_AT_03);
	}
}

uint16_t readOptical(uint8_t sensorToRead) {
	uint16_t voltage = 0, output = 0;
	ADMUX = (ADMUX & ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0))) | sensorADMux[sensorToRead];
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	voltage = ADC;
	output = convert_to_mm(voltage);
	return output;
}

uint16_t ADCValueLeftSensor() {
	ADMUX = (ADMUX & ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0))) | sensorADMux[DISTANCE_LEFT];
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}

/************************************************************************/
/* Optical sensors - end                                                */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/

uint16_t findMedian(uint8_t currentSensor) {
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
	if (current_pair == FRONT_AND_LEFT) {
		SENSOR_OUTPUT_FRONT_AND_LEFT |= (1<<TRIGGER_FRONT)|(1<<TRIGGER_LEFT);						// Trigger signal for sensors
		_delay_us(15);
		SENSOR_OUTPUT_FRONT_AND_LEFT &= ~((1<<TRIGGER_FRONT)|(1<<TRIGGER_LEFT));
		//Wait for input from sensors
		WAIT_FOR_INPUT_FRONT_AND_LEFT;										// Wait for echo signal start
	} else {
		SENSOR_OUTPUT_BACK_AND_RIGHT |= (1<<TRIGGER_BACK)|(1<<TRIGGER_RIGHT);						// Trigger signal for sensors
		_delay_us(15);
		SENSOR_OUTPUT_BACK_AND_RIGHT &= ~((1<<TRIGGER_BACK)|(1<<TRIGGER_RIGHT));
		//Wait for input from sensors
		WAIT_FOR_INPUT_BACK_AND_RIGHT;										// Wait for echo signal start
	}
	
	//Measure length of echo signal
	START_TIMER;
	while (distance<255) {								// Safecode so distance doesn't go over 255 (max for uint8_t)
		if (current_pair == FRONT_AND_LEFT) {
			if(FRONT_HIGH) {
				was_high[DISTANCE_FRONT] = 1;
			}
			if(LEFT_HIGH) {
				was_high[DISTANCE_LEFT] = 1;
			}
			if (!interrupted && !FRONT_HIGH && !done[DISTANCE_FRONT] && was_high[DISTANCE_FRONT]) {
				STOP_TIMER;																				// Need to stop timer to use distance variable
				distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer] = distance;						// Saves distance mesured by sensor
				START_TIMER;
				done[DISTANCE_FRONT] = 1;																// Set sensor to done
			}
			if (!interrupted && !LEFT_HIGH && !done[DISTANCE_LEFT] && was_high[DISTANCE_LEFT]) {
				STOP_TIMER;
				distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer] = distance;
				START_TIMER;
				done[DISTANCE_LEFT] = 1;
			}
		} else {
			if(BACK_HIGH) {
				was_high[DISTANCE_BACK] = 1;
			}
			if(RIGHT_HIGH) {
				was_high[DISTANCE_RIGHT] = 1;
			}
			if (!interrupted && !BACK_HIGH && !done[DISTANCE_BACK] && was_high[DISTANCE_BACK]) {
				STOP_TIMER;
				distanceBuffer[DISTANCE_BACK][distanceCircularBuffer] = distance;
				START_TIMER;
				done[DISTANCE_BACK] = 1;
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
	if (current_pair == FRONT_AND_LEFT) {
		if(!done[DISTANCE_FRONT]) {
			distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_FRONT] = findMedian(DISTANCE_FRONT);
		distanceSensors[DISTANCE_FRONT] = distanceBuffer[DISTANCE_FRONT][distanceCircularBuffer];
		
		if(!done[DISTANCE_LEFT]) {
			distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_LEFT] = findMedian(DISTANCE_LEFT);
		distanceSensors[DISTANCE_LEFT] = distanceBuffer[DISTANCE_LEFT][distanceCircularBuffer];
	} else {
		if(!done[DISTANCE_BACK]) {
			distanceBuffer[DISTANCE_BACK][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_BACK] = findMedian(DISTANCE_BACK);
		distanceSensors[DISTANCE_BACK] = distanceBuffer[DISTANCE_BACK][distanceCircularBuffer];
		
		if(!done[DISTANCE_RIGHT]) {
			distanceBuffer[DISTANCE_RIGHT][distanceCircularBuffer] = 255;
		}
		//distanceSensors[DISTANCE_RIGHT] = findMedian(DISTANCE_RIGHT);
		distanceSensors[DISTANCE_RIGHT] = distanceBuffer[DISTANCE_RIGHT][distanceCircularBuffer];
	}
	
	/************************************************************************/
	/* Optical sensors - start                                              */
	/*                                                                      */
	/*                                                                      */
	/*                                                                      */
	/*                                                                      */
	/*                                                                      */
	/************************************************************************/
	
	distanceSensors[DISTANCE_LEFT] = readOptical(DISTANCE_LEFT);
	distanceSensors[DISTANCE_RIGHT] = readOptical(DISTANCE_RIGHT);
	
	/*uint16_t ADCValue = ADCValueLeftSensor();
	
	distanceSensors[DISTANCE_LEFT] = (uint8_t)(ADCValue>>8);
	distanceSensors[DISTANCE_RIGHT] = (uint8_t)ADCValue;*/
	
	/************************************************************************/
	/* Optical sensors - end                                                */
	/*                                                                      */
	/*                                                                      */
	/*                                                                      */
	/*                                                                      */
	/*                                                                      */
	/************************************************************************/
	
	if (current_pair == FRONT_AND_LEFT) {
		current_pair = BACK_AND_RIGHT;
	} else {
		current_pair = FRONT_AND_LEFT;
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
		distance++;				// Increment distance every 58 us
}