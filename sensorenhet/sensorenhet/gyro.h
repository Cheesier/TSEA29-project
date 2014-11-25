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
//<<<<<<< HEAD
void updateGyroData();
uint8_t returnGyroData(uint8_t gyro_data);
uint8_t returnDegreesRotated();
/*
=======
int updateGyroData();
int returnGyroData(int gyro_data);
int returnDegreesRotated();
>>>>>>> origin/master*/
void resetDegreesRotated();

void initGyro();

#endif /* GYRO_H_ */