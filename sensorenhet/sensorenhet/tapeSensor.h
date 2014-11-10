/*
 * tapeSensor.h
 *
 * Created: 2014-11-10 14:01:33
 *  Author: Cavecanem
 */ 


#ifndef TAPESENSOR_H_
#define TAPESENSOR_H_

uint16_t getTapeData();
int convertToBit(int data);
void sendTapeData(uint16_t tape_data);

void calibrateTapeSensor(char on_tape);

#endif /* TAPESENSOR_H_ */