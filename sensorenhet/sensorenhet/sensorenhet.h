/*
 * sensorenhet.h
 *
 * Created: 11/11/2014 2:26:38 PM
 *  Author: jonny928
 */ 


#ifndef SENSORENHET_H_
#define SENSORENHET_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "tapeSensor.h"
#include "SPI.h"
#include "distanceSensor.h"

void initSensors();
int main();

#endif /* SENSORENHET_H_ */