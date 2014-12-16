/*
 * PD_regulator.c
 *
 * Created: 2014-11-17 12:09:52
 *  Author: Jonathan
 */ 

#include "PDregulator.h"
#include "Styrenhet.h"
#include <avr/interrupt.h>

#define D_SCALING 3

int active = 0;
int16_t sensorData[7];
int16_t PD_direction = 0;
uint8_t p = 11;		//11
uint8_t d = 40;		//40

int PDnewData = 0;

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
	sensorData[7] = sensorData[6];
	sensorData[6] = sensorData[5];
	sensorData[5] = sensorData[4];
	sensorData[4] = sensorData[3];
	sensorData[3] = sensorData[2];
	sensorData[2] = sensorData[1];
	sensorData[1] = sensorData[0];
	sensorData[0] = right-left;
	PDnewData = 1;
}
int16_t PDgetCorrection() {
	if(abs(sensorData[0] - sensorData[1]) < 30) {
		PD_direction = p * sensorData[0] + d * D_SCALING * (sensorData[0]-sensorData[1]);
	} else {
		PD_direction = 0;
	}
	PDnewData = 0;
	return PD_direction;
}

void setPD(uint8_t p_value, uint8_t d_value) {
	p = p_value;
	d = d_value;
}

void PDforward() {
	int16_t correction = PDgetCorrection();
	uint8_t left_speed = 255;
	uint8_t right_speed = 255;
	if (correction >= 0) {
		right_speed -= correction;
		/*if(right_speed<51) {
			right_speed = 51;
		}*/
	}
	else {
		left_speed += correction;
		/*if(left_speed<51) {
			left_speed = 51;
		}*/
	}
	PDTurning(left_speed, right_speed);
}