/*
 * algorithms.h
 *
 * Created: 2014-11-24 12:57:04
 *  Author: Jonathan
 */ 


#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include "message_handler.h"
#include <util/delay.h>
#include <avr/io.h>

extern uint16_t tape_data;

void interpretSensorData(char * sensorData);

#endif /* ALGORITHMS_H_ */