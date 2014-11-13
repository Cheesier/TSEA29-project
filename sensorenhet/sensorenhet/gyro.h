/*
 * gyro.h
 *
 * Created: 13/11/2014 13:19:13
 *  Author: Erik
 */


#ifndef GYRO_H_
#define GYRO_H_

uint8_t getGyroData();
uint8_t returnGyroData(uint8_t gyro_data);
uint8_t returnDegreesRotated();
void resetDegreesRotated();

void initGyro();

#endif /* GYRO_H_ */