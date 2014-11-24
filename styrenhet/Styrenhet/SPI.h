/*
 * SPI.h
 *
 * Created: 2014-11-06 14:56:39
 *  Author: Cavecanem
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_Init(void);

char SPI_Recive(void);
void SPI_Send(char dataout);
char SPI_Transceive(char dataout);
void receiveMessage();

#endif /* SPI_H_ */