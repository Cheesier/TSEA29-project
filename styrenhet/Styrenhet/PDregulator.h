/*
 * PD_regulator.h
 *
 * Created: 2014-11-17 12:10:19
 *  Author: Jonathan
 */ 

#include <inttypes.h>
#ifndef PDREGULATOR_H_
#define PDREGULATOR_H_

void PDactivate();
void PDdeactivate();
int PDisActive();
void PDupdateSensorData(uint8_t left, uint8_t right);
int16_t PDgetCorrection();
void setPD(uint8_t p_value, uint8_t d_value);
void PDforward();

extern int PDnewData;


#endif /* PD-REGULATOR_H_ */