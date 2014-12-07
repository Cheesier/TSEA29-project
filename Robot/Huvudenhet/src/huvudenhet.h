/*
 * huvudenhet.h
 *
 * Created: 2014-11-25 17:22:50
 *  Author: Jonathan
 */ 


#ifndef HUVUDENHET_H_
#define HUVUDENHET_H_

#define F_CPU 7372800UL

#define TRUE 1
#define FALSE 0

#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "motor.h"
#include "sensors.h"
#include "lcd.h"
#include "bluetooth.h"
#include "spi.h"
#include "message_handler.h"
#include "algorithms.h"
#include "pathList.h"

void autonomSet(char autonomOn);
extern int autonom;
extern uint8_t checkpoints[4];

void updateSensorData(void);


#endif /* HUVUDENHET_H_ */