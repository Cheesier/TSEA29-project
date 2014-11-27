/*
 * sensorenhet.h
 *
 * Created: 11/11/2014 2:26:38 PM
 *  Author: jonny928
 */


#ifndef SENSORENHET_H_
#define SENSORENHET_H_

#define START_TIMER TCCR1B |= (1 << CS10) | (1 << CS12);	// Set the prescaler to 1024
#define STOP_TIMER TCCR1B &= ~((1 << CS10) | (1 << CS12));

#define F_CPU 8000000UL

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "tapeSensor.h"
#include "gyro.h"
#include "SPI.h"
#include "distanceSensor.h"

void initSensors();
int main();
void tapeDone();

#endif /* SENSORENHET_H_ */