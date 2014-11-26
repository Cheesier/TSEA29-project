/*
 * gyro.h
 *
 * Created: 13/11/2014 13:19:13
 *  Author: Erik
 */


#ifndef GYRO_H_
#define GYRO_H_

extern uint16_t gyro_data_done;

void rotateDegrees(int degrees);
void updateGyroData();
int returnGyroData(int gyro_data);

int returnDegreesRotated();
/*
int updateGyroData();
int returnGyroData(int gyro_data);*/

void resetDegreesRotated();

void initGyro();

#endif /* GYRO_H_ */