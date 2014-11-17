/*
 * PD_regulator.h
 *
 * Created: 2014-11-17 12:10:19
 *  Author: Jonathan
 */ 

#include <inttypes.h>
#ifndef PD-REGULATOR_H_
#define PD-REGULATOR_H_

void activate();
void deactivate();
void updateSensorData(uint8_t left, uint8_t right);



#endif /* PD-REGULATOR_H_ */