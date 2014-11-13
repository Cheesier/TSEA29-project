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

#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)));

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR |= (1<<SPIE);				// Enable interrupts
	SPCR |= (1<<SPR0);				// Prescaler 16
}

// Receive from SPI
char SPI_Receive(void) {
	WAIT_FOR_TRANSFER;				// Wait for reception to complete
	return SPDR;					// Return Data Register
}

// Send over SPI
void SPI_Send(char dataout) {
	SPDR = dataout;					// Put package in Data Register
	WAIT_FOR_TRANSFER;				// Wait for transition to complete
	return;
}

// Receive a message from our main CPU
void receiveMessage() {
	char msg = SPI_Receive();
	char size = SPI_Receive();
	char header = msg >> 6;
	msg = msg & 0x3F;
	char speed;
	char left_dir, right_dir, left_speed, right_speed;
	char unknownMessage[size];	//couldn't be down in the default..

	if(header == 0x01) {							// Make sure that the message is meant for us
		switch(msg) {								// Identify the message and act accordingly
			case 0x01:	// Forward with pd
				speed = SPI_Receive();
				speed = speed << 1;
				//pdForward(speed);	TODO
				break;
			case 0x02:	// Turn on pd
				//setPd(on); TODO
				break;
			case 0x03:	// Turn off pd
				//setPd(off); TODO
				break;
			case 0x04:	// Switch forward/backward (used when reversing through the labyrinth)
				msg = SPI_Receive();
				setDirection(msg);
				break;
			case 0x05:	// Set the speed/direction for the different motors
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
				// setPD(p, d); to be implemented
				break;
			case 0x07:	// Move forward with the specified speed
				speed = SPI_Receive() << 1;
				driveForward(speed);
				break;
			case 0x08:	// Move backward with the specified speed
				speed = SPI_Receive() << 1;
				driveReverse(speed);
				break;
			case 0x09:	// Rotate left with the specified speed
				speed = SPI_Receive() << 1;
				rotateLeft(speed);
				break;
			case 0x0A:	// Rotate right with the specified speed
				speed = SPI_Receive() << 1;
				rotateRight(speed);
				break;
			case 0x0B:	// Close the claw
				gripClaw();
				break;
			case 0x0C:	// Open the claw
				releaseClaw();
				break;
<<<<<<< HEAD
			case 0x0D: // Stop the robot
				wheelSpeeds(0, 0);
=======
			case 0x0D: //STOP
				stopWheels();
>>>>>>> 4f28097f1329ab60515980c9d0e160f8f2b7f93d
				break;
			default:	// Fetch the message anyway
				for(int i = 0; i < size; i++) {
					unknownMessage[i] = SPI_Receive();
					errorMessage(unknownMessage);
				}
				break;
			}
		}
	else {			// In case of unexpected header, send an error message
		headerError(header);
	}
}

// Send back unknown messages to the control center
//TODO: Not any data
void errorMessage(char unknownMessage) {
	SPI_Send(0x3F);
}

// Send a message back to the control center if there's an header error
//TODO: Not any data
void headerError(int header) {
	SPI_Send(0x3F);
	return;
}