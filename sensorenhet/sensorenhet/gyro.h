/*
 * gyro.h
 *
 * Created: 13/11/2014 13:19:13
 *  Author: Erik
 */


#ifndef GYRO_H_
#define GYRO_H_

extern uint16_t gyro_data_done;

void rotateDegrees(uint16_t degrees);
int updateGyroData();
int returnGyroData(int gyro_data);
int returnDegreesRotated();
void resetDegreesRotated();

void initGyro();

#endif /* GYRO_H_ */