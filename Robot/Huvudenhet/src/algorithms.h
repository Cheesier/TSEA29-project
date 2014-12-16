/*
 * algorithms.h
 *
 * Created: 2014-11-24 12:57:04
 *  Author: Jonathan
 */ 


#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#define STATE_PD 0
#define STATE_GOTO_MIDDLE 1
#define STATE_ROTATE 2
#define STATE_FIND_WALLS 3
#define STATE_ROTATE_RESET 4
#define STATE_FIND_OBJECT 5
#define STATE_DONE 6

#define TYPE_DEAD_END 0
#define TYPE_TURN_LEFT 1
#define TYPE_TURN_RIGHT 2
#define TYPE_T_CROSS 3
#define TYPE_T_CROSS_LEFT 4
#define TYPE_T_CROSS_RIGHT 5
#define TYPE_INTERSECTION 6
#define TYPE_CORRIDOR 7
#define TYPE_NONE 255

#define WALL_COUNT 4

#define DIR_REVERSE 0
#define DIR_FORWARD 1

#include <stdint.h>

extern uint16_t tape_data;
extern uint8_t distance_data[4];
extern uint8_t middle_done;
extern uint8_t reversing;
extern uint8_t findingObject;
extern uint8_t wallsInRange[WALL_COUNT];


uint8_t countBits(uint16_t number);
void swapSensorDirections(uint8_t *sensorData);
void interpretSensorData(uint8_t *sensorData);

#endif /* ALGORITHMS_H_ */