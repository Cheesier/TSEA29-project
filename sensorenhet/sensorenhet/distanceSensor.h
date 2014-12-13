/*
 * distanceSensor.h
 *
 * Created: 11/11/2014 10:20:31 AM
 *  Author: jonny928
 */ 

#define DISTANCE_FRONT 0
#define DISTANCE_BACK 1
#define DISTANCE_LEFT 2
#define DISTANCE_RIGHT 3
#define SENSOR_COUNT 4

#ifndef DISTANCESENSOR_H_
#define DISTANCESENSOR_H_

uint16_t distance;
uint8_t interrupted;
extern uint16_t distanceSensors[SENSOR_COUNT];

void updateDistance();
void initDistance();


#endif /* DISTANCESENSOR_H_ */