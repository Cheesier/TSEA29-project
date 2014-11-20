/*
 * Styrenhet.h
 *
 * Created: 2014-11-06 11:24:50
 *  Author: Cavecanem
 */ 


#ifndef STYRENHET_H_
#define STYRENHET_H_
#include <stdint.h>
#include "PDregulator.h"

extern uint8_t maxSpeed;

void setDirection(uint8_t dir);

void driveForward();
void driveReverse();

void rotateLeft();
void rotateRight();

void PDTurning(uint8_t left_speed, uint8_t right_speed);
void softTurnLeft();
void softTurnRight();

void leftWheelDirection(uint8_t dir);
void rightWheelDirection(uint8_t dir);

void wheelSpeeds(uint8_t left_speed, uint8_t right_speed);

void releaseClaw();
void gripClaw();
void stopWheels();

#endif /* STYRENHET_H_ */