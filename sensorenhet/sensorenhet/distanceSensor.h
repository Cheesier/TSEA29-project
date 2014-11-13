/*
 * distanceSensor.h
 *
 * Created: 11/11/2014 10:20:31 AM
 *  Author: jonny928
 */ 

#define DISTANCE_FRONT 0
#define DISTANCE_RIGHT 1
#define DISTANCE_BACK 2
#define DISTANCE_LEFT 3
#define SENSOR_COUNT 4

#ifndef DISTANCESENSOR_H_
#define DISTANCESENSOR_H_


static int distance = 0;
static int interrupted = 0;
static uint8_t distanceSensors[SENSOR_COUNT];

uint8_t * getDistance();
int getDistanceVal();
void updateDistance();
void initDistance();


#endif /* DISTANCESENSOR_H_ */