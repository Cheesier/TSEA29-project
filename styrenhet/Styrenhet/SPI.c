/*
 * SPI.c
 *
 * Created: 2014-11-06 14:52:07
 *  Author: Cavecanem
 */ 
// CPU clock
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SPI.h"
#include "Styrenhet.h"

// SPI ports
#define SPI_SS PORTB4
#define SPI_MOSI PORTB5
#define SPI_MISO PORTB6
#define SPI_SCLK PORTB7

// SPI register
#define DDR_SPI DDRB

void SPI_Init(void) {
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR = (1>>SPIE);				// Enable interrupts
}

char SPI_Recieve(void) {
	while(!(SPSR & (1<<SPIF)));		// Wait for reception to complete
	return SPDR;					// Return Data Register
}

void SPI_Send(char dataout) {
	SPDR = dataout;					// Put package in Data Register
	while(!(SPSR & (1<<SPIF)));		// Wait for transition to complete
	return;
}

void startRecieveing() {
	char msg = SPI_Recieve();
	char header = msg >> 6;
	char size;
	msg = msg & 0x3F;
	char speed;	
	char l_dir, r_dir, l_speed, r_speed;
	
	if(header == 0x01) {
		switch(msg) {
			case 0x01: //Forward with pd
				size = SPI_Recieve();
				speed = SPI_Recieve();
				speed = speed << 1;
				//pdForward(speed);	to be implemented			
				break;
			case 0x02: //Turn on pd
				size = SPI_Recieve();
				//setPd(on); to be implemented
				break;
			case 0x03: //Turn off pd
				size = SPI_Recieve();
				//setPd(off); to be implemented
				break;
			case 0x04: //Switch forward/backward (used when reversing through the labyrinth)
				size = SPI_Recieve();
				msg = SPI_Recieve();
				setReverseMode(msg);
				break;
			case 0x05: //Set the speed/direction for the different motors
				size = SPI_Recieve();
				l_speed = SPI_Recieve();
				l_dir = l_speed >> 7;
				l_speed = l_speed << 1;
				leftWheelDirection(l_dir);				
				
				r_speed = SPI_Recieve();				
				r_dir = r_speed >> 7;
				r_speed = r_speed << 1;
				rightWheelDirection(r_dir);
				wheelSpeeds(l_speed, r_speed);
				break;
			case 0x06: //Set the p and d values
				size = SPI_Recieve();
				//setPD(p, d); to be implemented
				break;
			case 0x07: //Move forward with the specified speed
				size = SPI_Recieve();
				speed = SPI_Recieve() << 1;			
				driveForward(speed);
				break;
			case 0x08: //Move backward with the specified speed
				size = SPI_Recieve();
				speed = SPI_Recieve() << 1;
				driveReverse(speed);
				break;
			case 0x09: //Rotate left with the specified speed
				size = SPI_Recieve();
				speed = SPI_Recieve() << 1;
				rotateLeft(speed);
				break;
			case 0x0A: //Rotate right with the specified speed
				size = SPI_Recieve();
				speed = SPI_Recieve() << 1;
				rotateRight(speed);
				break;
			default:
				//Fetch the message anyway
				size = SPI_Recieve();
				char unknownMessage[size];
				for(int i = 0; i < size; i++) {
					unknownMessage[i] = SPI_Recieve();
				}			
				break;
		}
	}
	
} 