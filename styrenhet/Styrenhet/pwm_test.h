/*
 * pwm_test.h
 *
 * Created: 2014-11-06 11:22:09
 *  Author: Cavecanem
 */ 


#ifndef PWM_TEST_H_
#define PWM_TEST_H_
#include <stdint.h>

void init_pwm();
void setSpeed(uint8_t speed);
void setSpeeds(uint8_t speed_left, uint8_t speed_right);
void setLeftSpeed(uint8_t speed);
void setRightSpeed(uint8_t speed);
void clawGrip();
void clawRelease();
void clawEnable();
void clawDisable();



#endif /* PWM_TEST_H_ */