/*
 * PD_regulator.c
 *
 * Created: 2014-11-17 12:09:52
 *  Author: Jonathan
 */ 

#include "PDregulator.h"
#include "Styrenhet.h"

int active = 0;
uint8_t sensorData[4];
int8_t PD_direction = 0;
uint8_t p, d;
uint8_t speed;

void PDactivate() {
	active = 1;
}
void PDdeactivate() {
	active = 0;
	speed = 0;
}
int PDisActive() {
	return active;
}
void PDupdateSensorData(uint8_t left, uint8_t right) {
	sensorData[2] = sensorData[0];
	sensorData[3] = sensorData[1];
	sensorData[0] = left;
	sensorData[1] = right;
	PD_direction = p * (sensorData[1]-sensorData[0]) + d * ((sensorData[1]-sensorData[0])-(sensorData[3]-sensorData[2]));
}
int8_t PDgetCorrection() {
	return PD_direction;
}

void setPD(uint8_t p_value, uint8_t d_value) {
	p = p_value;
	d = d_value;
}

void PDsetSpeed(uint8_t speed_value) {
	speed = speed_value;
}

void PDforward() {
	while (PDisActive() && speed != 0)
	{
		int8_t correction = PD_direction;
		uint8_t left_speed = speed;
		uint8_t right_speed = speed;
		if (correction >= 0) {
			right_speed -= correction;
		}
		else {
			left_speed += correction;
		}
		softTurn(left_speed, right_speed);
	}
}