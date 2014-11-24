/*
 * PD_regulator.c
 *
 * Created: 2014-11-17 12:09:52
 *  Author: Jonathan
 */ 

#include "PDregulator.h"
#include "Styrenhet.h"
#include <avr/interrupt.h>

int active = 0;
int16_t sensorData[2];
int16_t PD_direction = 0;
uint8_t p = 15;
uint8_t d = 150;

void PDactivate() {
	active = 1;
}
void PDdeactivate() {
	active = 0;
}
int PDisActive() {
	return active;
}
void PDupdateSensorData(uint8_t left, uint8_t right) {
	sensorData[1] = sensorData[0];
	sensorData[0] = right-left;
}
int16_t PDgetCorrection() {
	cli();
	PD_direction = p * sensorData[0] + d * (sensorData[0]-sensorData[1]);
	sei();
	return PD_direction;
}

void setPD(uint8_t p_value, uint8_t d_value) {
	p = p_value;
	d = d_value;
}

void PDforward() {
	while (PDisActive())
	{
		int16_t correction = PDgetCorrection();
		uint8_t left_speed = 255;
		uint8_t right_speed = 255;
		if (correction >= 0) {
			right_speed -= correction/4;
			if(right_speed<51) {
				right_speed = 51;
			}
		}
		else {
			left_speed += correction/4;
			if(left_speed<51) {
				left_speed = 51;
			}
		}
		PDTurning(left_speed, right_speed);
	}
}