/*
 * Styrenhet.c
 *
 * Created: 03/11/2014 13:13:22
 *  Author: Erik
 */

// CPU clock
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Styrenhet.h"
#include "SPI.h"

//PWM
#include "pwm_test.h"

// Pins handling wheel direction
#define WHEEL_DIRECTION_L PORTA0
#define WHEEL_DIRECTION_R PORTA1

//Defines the direction of the robot
#define FORWARD 1
#define REVERSE 0

char direction = FORWARD;

// Receiving and sending could be done by the same function but this seem clearer to me

int main(void) {
	SPI_Init();						// Initiate SPI as a slaves
	init_pwm();
	//int direction = FORWARD;
	//softTurn(255,127);	
	while(1) {
		gripClaw();
		_delay_ms(2500);
		releaseClaw();
		_delay_ms(500);
	}
}

void setReverseMode(uint8_t dir) {
	if(dir == 1) {
		direction = FORWARD;
	}
	else if(dir == 0) {
		direction = REVERSE;
	}
}

void driveForward(uint8_t speed) {
	if(direction == REVERSE) {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Set wheel direction to reverse by
		PORTA &= ~(1<<WHEEL_DIRECTION_R);		// clearing the direction pins
		setSpeed(speed);
	}
	else {
		PORTA |= (1<<WHEEL_DIRECTION_L);		// Set wheel direction to forward by
		PORTA |= (1<<WHEEL_DIRECTION_R);		// setting the direction pins
		setSpeed(speed);
	}
	return;
}

void driveReverse(uint8_t speed) {
	if(direction == REVERSE) {
		PORTA |= (1<<WHEEL_DIRECTION_L);		// Set wheel direction to forward by
		PORTA |= (1<<WHEEL_DIRECTION_R);		// setting the direction pins
		setSpeed(speed);
	}
	else {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Set wheel direction to reverse by
		PORTA &= ~(1<<WHEEL_DIRECTION_R);		// clearing the direction pins
		setSpeed(speed);
	}
	return;
}

void rotateLeft(uint8_t speed) {
	if(direction == REVERSE){
		PORTA |= (1<<WHEEL_DIRECTION_L);		// Make the robot turn right by setting
		PORTA &= ~(1<<WHEEL_DIRECTION_R);		// the left wheels to forward and vice versa
		setSpeed(speed);
	}
	else {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Make the robot turn left by setting
		PORTA |= (1<<WHEEL_DIRECTION_R);		// the right wheels to forward and vice versa
		setSpeed(speed);
	}
	return;
}

void rotateRight(uint8_t speed) {
	if(direction == REVERSE){
		PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Make the robot turn left by setting
		PORTA |= (1<<WHEEL_DIRECTION_R);		// the right wheels to forward and vice versa
		setSpeed(speed);
	}
	else {
		PORTA |= (1<<WHEEL_DIRECTION_L);		// Make the robot turn right by setting
		PORTA &= ~(1<<WHEEL_DIRECTION_R);		// the left wheels to forward and vice versa
		setSpeed(speed);
	}
	return;
}

void softTurn(uint8_t leftspeed, uint8_t rightspeed) {
	PORTA |= (1<<WHEEL_DIRECTION_L);
	PORTA |= (1<<WHEEL_DIRECTION_R);
	setSpeeds(leftspeed, rightspeed);				// The implementation of pwm() can handle separate speeds for both sides
	return;
}

void softTurnReverse(uint8_t leftspeed, uint8_t rightspeed) {
	PORTA &= ~(1<<WHEEL_DIRECTION_L);
	PORTA &= ~(1<<WHEEL_DIRECTION_R);
	setSpeeds(leftspeed, rightspeed);				// The implementation of pwm() can handle separate speeds for both sides
	return;
}

void releaseClaw() {
	clawEnable();
	clawRelease();
	_delay_ms(300);
	clawDisable();
}

void gripClaw() {
	clawEnable();
	clawGrip();	
}

void leftWheelDirection(uint8_t dir) {
	if(direction == REVERSE) {
		if(dir == 1) {
			dir = 0;
		}
		else {
			dir = 1;
		}
	}
	
	if(dir == 1) {
		PORTA |= (1 << WHEEL_DIRECTION_L);		
	}
	else if(dir == 0) {
		PORTA &= ~(1 << WHEEL_DIRECTION_L);
	}
}

void rightWheelDirection(uint8_t dir) {
	if(direction == REVERSE) {
		if(dir == 1) {
			dir = 0;
		}
		else {
			dir = 1;
		}
	}
	
	if(dir == 1) {
		PORTA |= (1 << WHEEL_DIRECTION_R);
	}
	else if(dir == 0) {
		PORTA &= ~(1 << WHEEL_DIRECTION_R);
	}
}

void wheelSpeeds(uint8_t l_speed, uint8_t r_speed) {
	setSpeeds(l_speed, r_speed);
}