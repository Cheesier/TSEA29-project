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

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR = (1>>SPIE);				// Enable interrupts
}

// Receive from SPI
char SPI_Receive(void) {
	while(!(SPSR & (1<<SPIF)));		// Wait for reception to complete
	return SPDR;					// Return Data Register
}

// Send over SPI
void SPI_Send(char dataout) {
	SPDR = dataout;					// Put package in Data Register
	while(!(SPSR & (1<<SPIF)));		// Wait for transition to complete
	return;
}

// Receive a message from our main CPU
void receiveMessage() {
	char msg = SPI_Receive();
	char header = msg >> 6;
	char size;
	msg = msg & 0x3F;
	char speed;	
	char left_dir, right_dir, left_speed, right_speed;
	
	if(header == 0x01) {							// Make sure that the message is meant for us
		switch(msg) {								// Identify the message and act accordingly 
			case 0x01:	// Forward with pd
				size = SPI_Receive();
				speed = SPI_Receive();
				speed = speed << 1;
				//pdForward(speed);	TODO			
				break;
			case 0x02:	// Turn on pd
				size = SPI_Receive();
				//setPd(on); TODO
				break;
			case 0x03:	// Turn off pd
				size = SPI_Receive();
				//setPd(off); TODO
				break;
			case 0x04:	// Switch forward/backward (used when reversing through the labyrinth)
				size = SPI_Receive();
				msg = SPI_Receive();
				setReverseMode(msg);
				break;
			case 0x05:	// Set the speed/direction for the different motors
				size = SPI_Receive();
				left_speed = SPI_Receive();
				left_dir = left_speed >> 7;
				left_speed = left_speed << 1;
				leftWheelDirection(left_dir);				
				
				right_speed = SPI_Receive();				
				right_dir = right_speed >> 7;
				right_speed = right_speed << 1;
				rightWheelDirection(right_dir);
				wheelSpeeds(left_speed, right_speed);
				break;
			case 0x06:	// Set the p and d values
				size = SPI_Receive();
				// setPD(p, d); to be implemented
				break;
			case 0x07:	// Move forward with the specified speed
				size = SPI_Receive();
				speed = SPI_Receive() << 1;			
				driveForward(speed);
				break;
			case 0x08:	// Move backward with the specified speed
				size = SPI_Receive();
				speed = SPI_Receive() << 1;
				driveReverse(speed);
				break;
			case 0x09:	// Rotate left with the specified speed
				size = SPI_Receive();
				speed = SPI_Receive() << 1;
				rotateLeft(speed);
				break;
			case 0x0A:	// Rotate right with the specified speed
				size = SPI_Receive();
				speed = SPI_Receive() << 1;
				rotateRight(speed);
				break;
			case 0x0B:	// Close the claw
				size = SPI_Receive();
				gripClaw();
				break;
			case 0x0C:	// Open the claw
				size = SPI_Receive();
				releaseClaw();
				break;
			default:	// Fetch the message anyway
				size = SPI_Receive();
				char unknownMessage[size];
				for(int i = 0; i < size; i++) {
					unknownMessage[i] = SPI_Receive();
				}
				break;
		}
	}

}