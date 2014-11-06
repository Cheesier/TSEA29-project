/*
 * Styrenhet.h
 *
 * Created: 2014-11-06 11:24:50
 *  Author: Cavecanem
 */ 


#ifndef STYRENHET_H_
#define STYRENHET_H_
#include <stdint.h>

void SPI_Init(void);
char SPI_Recive(void);
void SPI_Send(char dataout);
void driveForward(uint8_t speed);
void driveReverse(uint8_t speed);
void rotateLeft(uint8_t speed);
void rotateRight(uint8_t speed);
void softTurn(uint8_t leftspeed, uint8_t rightspeed);
void softTurnReverse(uint8_t leftspeed, uint8_t rightspeed);
void releaseClaw();
void gripClaw();



#endif /* STYRENHET_H_ */