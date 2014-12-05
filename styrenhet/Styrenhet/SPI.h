/*
 * SPI.h
 *
 * Created: 2014-11-06 14:56:39
 *  Author: Cavecanem
 */ 


#ifndef SPI_H_
#define SPI_H_

#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)));

void SPI_Init(void);

char SPI_Recive(void);
void SPI_Send(uint8_t dataout);
char SPI_Transceive(uint8_t dataout);
void receiveMessage(void);
void send_REQ_styrenhet(void);

#endif /* SPI_H_ */