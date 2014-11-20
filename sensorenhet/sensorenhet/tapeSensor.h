/*
 * tapeSensor.h
 *
 * Created: 2014-11-10 14:01:33
 *  Author: Cavecanem
 */


#ifndef TAPESENSOR_H_
#define TAPESENSOR_H_

#define F_CPU 8000000UL

extern uint16_t tape_data_done;

int convertToBit(int data);

void calibrateTapeSensor();
void setOnTape();
void setOffTape();

#endif /* TAPESENSOR_H_ */