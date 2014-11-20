/*
 * motor.h
 *
 * Created: 11/19/2014 4:32:26 PM
 *  Author: Oscar
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_MAX_SPEED = 127

static char motor_left_speed;
static char motor_right_speed;


#endif /* MOTOR_H_ */

void motor_claw_close(void);
void motor_claw_open(void);