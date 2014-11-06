#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pwm_test.h"

#define CLAW_TIMER TCCR0
#define WHEEL_TIMER_A TCCR1A
#define WHEEL_TIMER_B TCCR1B
#define LEFT_WHEEL_VALUE OCR1AL
#define RIGHT_WHEEL_VALUE OCR1BL
#define CLAW_VALUE OCR0

void init_pwm(){
/************************************************************************/
//	TCCR0, 8-bit counter, page 77
//	Controls TEH CLAW
//	WGM decides the pwm mode			| WGM00 & WGM01 => fast pwm
//	CS sets the prescaler				| CS02 & CS00 => CLK/1024
//	COM sets the compare output mode	| COM01 => Clear OC0 on match, set on BOTTOM
/************************************************************************/
CLAW_TIMER |= (1 << WGM00) | (1 << WGM01) | (1 << CS02) | (1 << CS00);
DDRB |= (1 << PORTB3); //sets OC0 as output

/************************************************************************/
//	TCCR1A:B, 16-bit counter (running as 8-bit counter), page 104
//	Controls the wheel servos
//	WGM decides the pwm	mode			| WGM10 & WGM12 => fast pwm, 8-bit
//	CS sets the prescaler				| CS12 & CS10 => CLK/1024
//	COM sets the compare output mode	| COM1A1 & COM1B1 => Clear OC1A:B on match, set on BOTTOM
/************************************************************************/
WHEEL_TIMER_A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
WHEEL_TIMER_B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
DDRD |= (1 << PORTD4) | (1 << PORTD5); //sets 0C1A:B as outputs	
}

//Sets the duty cycle of both motors to speed
void setSpeed(int speed) {
	LEFT_WHEEL_VALUE = speed;
	RIGHT_WHEEL_VALUE = speed;	
}

//Sets the duty cycle of the left motors to speed_left and the right motors to speed_right
void setSpeeds(int speed_left, int speed_right) {	
	LEFT_WHEEL_VALUE = speed_left;	
	RIGHT_WHEEL_VALUE = speed_right;
}

//Makes the claw grip
void clawGrip() {
	CLAW_VALUE = 5;	
}

//Makes the claw release its grip
void clawRelease() {
	CLAW_VALUE = 11;
}

void clawEnable() {
	CLAW_TIMER |= (1<<COM01);
}

void clawDisable() {
	CLAW_TIMER &= ~(1<<COM01);
}


/*int main(void){	
	init_pwm();
	
	
	while(1){
		CLAW_VALUE = 13;
		LEFT_WHEEL_VALUE = 255;
		RIGHT_WHEEL_VALUE = 255;
		
		_delay_ms(4000);
		
		CLAW_VALUE = 6;
		LEFT_WHEEL_VALUE = 0;
		RIGHT_WHEEL_VALUE = 0;		
		
		_delay_ms(4000);
	}	
	return 0;
}*/