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

// Pins handling wheel direction
#define WHEEL_DIRECTION_L PORTA0
#define WHEEL_DIRECTION_R PORTA1

// Defines the direction of the wheels
#define FORWARD 1
#define REVERSE 0

char direction = FORWARD;
#define MAXSPEED 255
uint8_t rotateSpeed = 150;
uint8_t speed = 128;

int main(void) {
	SPI_Init();								// Initiate SPI as a slaves
	init_pwm();								// Initiates the pins used for PWM
	sei();
	
	while(1) {
		if(PDnewData && PDisActive()) {
			PDforward();
		}
		_delay_us(1);
	}
}

// Set the character keeping track of the direction the robot is traveling in
void setDirection(uint8_t dir) {
	if(dir == 1) {
		direction = FORWARD;
	}
	else if(dir == 0) {
		direction = REVERSE;
	}
}

void setCurrentSpeed(uint8_t _speed) {
	speed = _speed;
}

// The robot drives forward
void driveForward() {	
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
}

// The robot drives in reverse
void driveReverse() {	
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
}

// The robot rotates to the left
void rotateLeft() {	
	if(direction == REVERSE){
		PORTA |= (1<<WHEEL_DIRECTION_L);		// Make the robot turn right by setting
		PORTA &= ~(1<<WHEEL_DIRECTION_R);		// the left wheels to forward and vice versa
		setSpeed(rotateSpeed);
	}
	else {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Make the robot turn left by setting
		PORTA |= (1<<WHEEL_DIRECTION_R);		// the right wheels to forward and vice versa
		setSpeed(rotateSpeed);
	}
}

// The robot rotates to the right
void rotateRight() {	
	if(direction == REVERSE){
		PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Make the robot turn left by setting
		PORTA |= (1<<WHEEL_DIRECTION_R);		// the right wheels to forward and vice versa
		setSpeed(rotateSpeed);
	}
	else {
		PORTA |= (1<<WHEEL_DIRECTION_L);		// Make the robot turn right by setting
		PORTA &= ~(1<<WHEEL_DIRECTION_R);		// the left wheels to forward and vice versa
		setSpeed(rotateSpeed);
	}	
}


// The robot makes a soft turn
// Turn direction is decided by the input parameters
void PDTurning(uint16_t left_speed, uint16_t right_speed) {
	left_speed = (left_speed * speed)/MAXSPEED;
	right_speed = (right_speed * speed)/MAXSPEED;
	if(direction == REVERSE) {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);
		PORTA &= ~(1<<WHEEL_DIRECTION_R);
	}
	else {	
		PORTA |= (1<<WHEEL_DIRECTION_L);
		PORTA |= (1<<WHEEL_DIRECTION_R);
	}
	setSpeeds(left_speed, right_speed);				// The PWM implementation can handle separate speeds for both sides
	return;
}

void softTurnLeft() {
	uint8_t left_speed = speed/3;
	uint8_t right_speed = speed;
	if(direction == REVERSE) {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);
		PORTA &= ~(1<<WHEEL_DIRECTION_R);
		setSpeeds(right_speed, left_speed);
		return;
	}
	PORTA |= (1<<WHEEL_DIRECTION_L);
	PORTA |= (1<<WHEEL_DIRECTION_R);
	setSpeeds(left_speed, right_speed);				// The PWM implementation can handle separate speeds for both sides
	return;
}

// The robot makes a soft turn in reverse
// Turn direction is decided by the input parameters
void softTurnRight() {	
	uint8_t left_speed = speed;
	uint8_t right_speed = speed/3;
	if(direction == REVERSE) {
		PORTA &= ~(1<<WHEEL_DIRECTION_L);
		PORTA &= ~(1<<WHEEL_DIRECTION_R);
		setSpeeds(right_speed, left_speed);
		return;
	}
	PORTA |= (1<<WHEEL_DIRECTION_L);
	PORTA |= (1<<WHEEL_DIRECTION_R);
	setSpeeds(left_speed, right_speed);				// The PWM implementation can handle separate speeds for both sides
	return;
}

// Set the direction of the left wheel pair according to input
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

// Set the direction of the right wheel pair according to input
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

// Set the speed of both wheel pairs
// QUESTION: Why is this needed?
void wheelSpeeds(uint8_t left_speed, uint8_t right_speed) {
	if(direction == REVERSE) {
		uint8_t temp = left_speed;
		left_speed = right_speed;
		right_speed = temp;
	}
	setSpeeds(left_speed, right_speed);
}

void stopWheels() {	
	setSpeeds(0,0);	
}

// Calls PWM functions to release the claw
void releaseClaw() {
	clawEnable();
	clawRelease();
	_delay_ms(300);
	clawDisable();
}

// Calls PWM functions to close the claw
void gripClaw() {
	clawEnable();
	clawGrip();
}

void forwardToMiddle() {
	setSpeed(128);
	if (direction == FORWARD)
		_delay_ms(100);
	if (direction == REVERSE)
		_delay_ms(160);
	stopWheels();
	//cli();  // This is already done in the SPI interrupt
	send_REQ_styrenhet();
	SPSR &= ~(1<<SPIF);
	SPI_Send(0x05);
	SPI_Send(0x00);
	//sei();
}