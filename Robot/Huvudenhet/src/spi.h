/*
 * spi.h
 *
 * Created: 11/10/2014 3:37:13 PM
 *  Author: Oscar
 */

#include <stdint.h>

#define SS_STYR		PORTB4
#define SS_SENSOR	PORTB3

// REQ signals
#define REQ_STYRENHET PORTD2
#define REQ_SENSORENHET PORTD3

// tmep
extern uint8_t req_set;

void spi_init(void);
char spi_transceive(uint8_t address, uint8_t data);
char spi_read(uint8_t address);
void spi_write(uint8_t address, uint8_t data);

void spi_send(uint8_t header, uint8_t size, uint8_t* data);

int isGyroDone(void);
void resetGyroDone(void);
void setGyroDone(void);

void gyroModeON();
void gyroModeOFF();