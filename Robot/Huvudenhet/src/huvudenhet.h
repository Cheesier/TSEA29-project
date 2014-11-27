/*
 * huvudenhet.h
 *
 * Created: 2014-11-25 17:22:50
 *  Author: Jonathan
 */ 


#ifndef HUVUDENHET_H_
#define HUVUDENHET_H_

#define F_CPU 7372800UL

#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "motor.h"
#include "sensors.h"
#include "lcd.h"
#include "bluetooth.h"
#include "spi.h"
#include "message_handler.h"
#include "algorithms.h"
#include "pathList.h"

void autonomSet(char autonomOn);


#endif /* HUVUDENHET_H_ */