/*
 * spi.h
 *
 * Created: 11/10/2014 3:37:13 PM
 *  Author: Oscar
 */ 

#define SS_STYR		PORTB3
#define SS_SENSOR	PORTB4

void spi_init(void);
char spi_transceive(char address, char data);
char spi_read(char address);
void spi_write(char address, char data);

void spi_send(char header, char size, char* data);