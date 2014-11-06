/*
 * Styrenhet.h
 *
 * Created: 2014-11-06 11:24:50
 *  Author: Cavecanem
 */ 


#ifndef STYRENHET_H_
#define STYRENHET_H_

void SPI_Init(void);
char SPI_Recive(void);
void SPI_Send(char dataout);
void driveForward(int speed);
void driveReverse(int speed);
void rotateLeft(int speed);
void rotateRight(int speed);
void softTurn(int leftspeed, int rightspeed);
void softTurnReverse(int leftspeed, int rightspeed);



#endif /* STYRENHET_H_ */