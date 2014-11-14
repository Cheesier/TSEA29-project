/*
 * tapeSensor.h
 *
 * Created: 2014-11-10 14:01:33
 *  Author: Cavecanem
 */


#ifndef TAPESENSOR_H_
#define TAPESENSOR_H_

uint8_t getTapeData();
int convertToBit(int data);
uint16_t returnTapeData(uint16_t tape_data);

void calibrateTapeSensor();
void setOnTape();
void setOffTape();

#endif /* TAPESENSOR_H_ */