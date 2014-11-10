/*
 * pwm.c
 *
 * Created: 03/11/2014 12:40:19
 * Author: Cavecanem
 */

// CPU clock
#define F_CPU 8000000

#include "pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Pins controlling the wheels and teh claw
#define CLAW_TIMER TCCR0
#define WHEEL_TIMER_A TCCR1A
#define WHEEL_TIMER_B TCCR1B
#define LEFT_WHEEL_VALUE OCR1AL
#define RIGHT_WHEEL_VALUE OCR1BL
#define LEFT_WHEEL_PIN PORTD5
#define RIGHT_WHEEL_PIN PORTD4
#define CLAW_PIN PORTB3
#define CLAW_VALUE OCR0

void init_pwm() {
/************************************************************************/
//	TCCR0, 8-bit counter, page 77
//	Controls TEH CLAW
//	WGM decides the pwm mode			| WGM00 & WGM01 => fast pwm
//	CS sets the prescaler				| CS02 & CS00 => CLK/1024
//	COM sets the compare output mode	| COM01 => Clear OC0 on match, set on BOTTOM
/************************************************************************/
CLAW_TIMER |= (1 << WGM00) | (1 << WGM01) | (1 << CS02) | (1 << CS00);
DDRB |= (1 << CLAW_PIN); // sets OC0 as output

/************************************************************************/
//	TCCR1A:B, 16-bit counter (running as 8-bit counter), page 104
//	Controls the wheel servos
//	WGM decides the pwm	mode			| WGM10 & WGM12 => fast pwm, 8-bit
//	CS sets the prescaler				| CS12 & CS10 => CLK/1024
//	COM sets the compare output mode	| COM1A1 & COM1B1 => Clear OC1A:B on match, set on BOTTOM
/************************************************************************/
WHEEL_TIMER_A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
WHEEL_TIMER_B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
DDRD |= (1 << RIGHT_WHEEL_PIN) | (1 << LEFT_WHEEL_PIN); // sets 0C1A:B as outputs (OC1A = Left, OC1B = Right)	
}

// Sets the duty cycle of both motors to speed
void setSpeed(uint8_t speed) {
	LEFT_WHEEL_VALUE = speed;
	RIGHT_WHEEL_VALUE = speed;	
}

// Sets the duty cycle of the left motors to speed_left and the right motors to speed_right
void setSpeeds(uint8_t speed_left, uint8_t speed_right) {	
	LEFT_WHEEL_VALUE = speed_left;	
	RIGHT_WHEEL_VALUE = speed_right;
}

// Sets the speed for the left wheel pair
void setLeftSpeed(uint8_t speed) {
	LEFT_WHEEL_VALUE = speed;
}

// Sets the speed for the right wheel pair
void setRightSpeed(uint8_t speed) {
	RIGHT_WHEEL_VALUE = speed;
}

// Makes the claw grip
void clawGrip() {
	CLAW_VALUE = 5;	
}

// Makes the claw release its grip
void clawRelease() {
	CLAW_VALUE = 11;
}

// Enables the claw for gripping
void clawEnable() {
	CLAW_TIMER |= (1<<COM01);
}

// Disables the claw for when it's not in use since there is no need for it to constantly force itself open
// Saves battery life, motor wear and our ears
void clawDisable() {
	CLAW_TIMER &= ~(1<<COM01);
}