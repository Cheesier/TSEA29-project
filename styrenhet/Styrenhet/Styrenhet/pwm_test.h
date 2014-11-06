/*
 * pwm_test.h
 *
 * Created: 2014-11-06 11:22:09
 *  Author: Cavecanem
 */ 


#ifndef PWM_TEST_H_
#define PWM_TEST_H_

void init_pwm();
void setSpeed(int speed);
void setSpeeds(int speed_left, int speed_right);
void clawGrip();
void clawRelease();
void clawEnable();
void clawDisable();



#endif /* PWM_TEST_H_ */