/*
 * algorithms.h
 *
 * Created: 2014-11-24 12:57:04
 *  Author: Jonathan
 */ 


#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include <stdint.h>

extern uint16_t tape_data;
extern uint16_t distance_data[4];

void interpretSensorData(char * sensorData);

#endif /* ALGORITHMS_H_ */