/*
 * pwm.h
 *
 * Created: 2014-11-06 11:22:09
 *  Author: Cavecanem
 */ 


#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>

void init_pwm();

void setSpeed(uint8_t speed);
void setSpeeds(uint8_t left_speed, uint8_t right_speed);

void setLeftSpeed(uint8_t speed);
void setRightSpeed(uint8_t speed);

void clawGrip();
void clawRelease();
void clawEnable();
void clawDisable();
void wheelsEnable();
void wheelsDisable();

#endif /* PWM_H_ */