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
extern uint8_t distance_data[4];
extern int middle_done;


int checkReversing();
void swapSensorDirections(uint8_t *sensorData);
void interpretSensorData(uint8_t *sensorData);

#endif /* ALGORITHMS_H_ */