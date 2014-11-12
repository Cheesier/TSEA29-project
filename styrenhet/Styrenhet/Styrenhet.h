/*
 * Styrenhet.h
 *
 * Created: 2014-11-06 11:24:50
 *  Author: Cavecanem
 */ 


#ifndef STYRENHET_H_
#define STYRENHET_H_
#include <stdint.h>

void setDirection(uint8_t dir);

void driveForward(uint8_t speed);
void driveReverse(uint8_t speed);

void rotateLeft(uint8_t speed);
void rotateRight(uint8_t speed);

void softTurn(uint8_t left_speed, uint8_t right_speed);
void softTurnReverse(uint8_t left_speed, uint8_t right_speed);

void leftWheelDirection(uint8_t dir);
void rightWheelDirection(uint8_t dir);

void wheelSpeeds(uint8_t left_speed, uint8_t right_speed);

void releaseClaw();
void gripClaw();
void stopWheels();

#endif /* STYRENHET_H_ */