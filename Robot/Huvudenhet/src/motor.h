/*
 * motor.h
 *
 * Created: 11/19/2014 4:32:26 PM
 *  Author: Oscar
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_


#endif /* MOTOR_H_ */

void init_motor(void);

void motor_claw_close(void);
void motor_claw_open(void);

void motor_set_speed(char speed);
void motor_set_direction(char dir);
void motor_stop(void);
void motor_go_forward(void);
void motor_go_backward(void);
void motor_rotate_left(void);
void motor_rotate_right(void);
