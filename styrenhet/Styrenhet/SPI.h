/*
 * SPI.h
 *
 * Created: 2014-11-06 14:56:39
 *  Author: Cavecanem
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "Styrenhet.h"

void SPI_Init(void);

char SPI_Recive(void);
void SPI_Send(char dataout);
char SPI_Transceive(char dataout);
void errorMessage(int size, char *unknownMessage);
void headerError(int header, int size, char *unknownMessage);

#endif /* SPI_H_ */