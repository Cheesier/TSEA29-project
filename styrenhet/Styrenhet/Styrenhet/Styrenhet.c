/*
 * Styrenhet.c
 *
 * Created: 04/11/2014 10:46:25
 *  Author: Erik
 */
/*
 * Atmega16_Test.c
 * Created: 03/11/2014 13:13:22
 *  Author: Erik
 */

// CPU clock
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Styrenhet.h"

//#include pwm lol
#include "pwm_test.h"

// SPI ports
#define SPI_SS PORTB4
#define SPI_MOSI PORTB5
#define SPI_MISO PORTB6
#define SPI_SCLK PORTB7

// SPI register
#define DDR_SPI DDRB

// Pins handling wheel direction
#define WHEEL_DIRECTION_L PORTA0
#define WHEEL_DIRECTION_R PORTA1

// Pins handling wheel speed
#define WHEEL_SPEED_L PORTD4
#define WHEEL_SPEED_R PORTD5

// Pin handling CLAW
#define CLAW_CONTROL PORTB3

void SPI_Init(void){
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR = (1>>SPIE);				// Enable interrupts
}

char SPI_Recive(void){
	while(!(SPSR & (1<<SPIF)));		// Wait for reception to complete
	return SPDR;					// Return Data Register
}

void SPI_Send(char dataout){
	SPDR = dataout;					// Put package in Data Register
	while(!(SPSR & (1<<SPIF)));		// Wait for transition to complete
	return;
}

// Receiving and sending could be done by the same function but this seem clearer to me

int main(void) {
	SPI_Init();						// Initiate SPI as a slaves
	init_pwm();
	softTurn(255,127);
	while(1) {
		clawGrip();
		_delay_ms(500);
		clawRelease();
		_delay_ms(500);
	}
}

void driveForward(int speed) {
	PORTA |= (1<<WHEEL_DIRECTION_L);		// Set wheel direction to forward by
	PORTA |= (1<<WHEEL_DIRECTION_R);		// setting the direction pins
	setSpeed(speed);
	return;
}

void driveReverse(int speed) {
	PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Set wheel direction to reverse by
	PORTA &= ~(1<<WHEEL_DIRECTION_R);		// clearing the direction pins
	setSpeed(speed);
	return;
}

void rotateLeft(int speed) {
	PORTA &= ~(1<<WHEEL_DIRECTION_L);		// Make the robot turn left by setting
	PORTA |= (1<<WHEEL_DIRECTION_R);		// the right wheels to forward and vice versa
	setSpeed(speed);
	return;
}

void rotateRight(int speed) {
	PORTA |= (1<<WHEEL_DIRECTION_L);		// Make the robot turn right by setting
	PORTA &= ~(1<<WHEEL_DIRECTION_R);		// the left wheels to forward and vice versa
	setSpeed(speed);
	return;
}

void softTurn(int leftspeed, int rightspeed) {
	PORTA |= (1<<WHEEL_DIRECTION_L);
	PORTA |= (1<<WHEEL_DIRECTION_R);
	setSpeeds(leftspeed, rightspeed);				// The implementation of pwm() can handle separate speeds for both sides
	return;
}

void softTurnReverse(int leftspeed, int rightspeed) {
	PORTA &= ~(1<<WHEEL_DIRECTION_L);
	PORTA &= ~(1<<WHEEL_DIRECTION_R);
	setSpeeds(leftspeed, rightspeed);				// The implementation of pwm() can handle separate speeds for both sides
	return;
}

// Varför är PORTA rosa?