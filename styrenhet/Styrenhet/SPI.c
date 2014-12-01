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
#include "PDregulator.h"

// SPI ports
#define SPI_SS PORTB4
#define SPI_MOSI PORTB5
#define SPI_MISO PORTB6
#define SPI_SCLK PORTB7

#define REQ PORTD0

// SPI register
#define DDR_SPI DDRB

#define WAIT_FOR_TRANSFER while(!(SPSR & (1<<SPIF)));

// Initiates the SPI
void SPI_Init(void) {
	DDR_SPI = (1<<SPI_MISO);		// Set MISO output
	SPCR = (1<<SPE);				// Enable SPI
	SPCR |= (1<<SPIE);				// Enable interrupts
	SPCR |= (1<<SPR0);				// Prescaler 16
	
	DDRD |= (1<<REQ);
}

// Receive from SPI
char SPI_Receive(void) {
	return SPI_Transceive(0x00);
}

// Send over SPI
void SPI_Send(char dataout) {
	SPI_Transceive(dataout);
}

char SPI_Transceive(char dataout) {
	SPDR = dataout;
	WAIT_FOR_TRANSFER;
	return SPDR;
}

ISR(SPISTC_vect) {
	cli();
	char msg = SPDR;
	char size = SPI_Receive();
	char header = msg >> 6;
	msg = msg & 0x3F;
	char speed;
	char left_sensor, right_sensor;
	uint8_t d, p;
	char left_dir, right_dir, left_speed, right_speed;
	char unknownMessage[size];	//couldn't be down in the default..
		if(header == 0x01) {							// Make sure that the message is meant for us
			switch(msg) {								// Identify the message and act accordingly
				case 0x01:	// Forward with pd
					PDactivate();
					break;
				case 0x02:
					left_sensor = SPI_Receive();
					right_sensor = SPI_Receive();
					PDupdateSensorData(left_sensor, right_sensor);
					break;
				case 0x03:
					break;
				case 0x04:	// Switch forward/backward (used when reversing through the labyrinth)
					msg = SPI_Receive();
					setDirection(msg);
					break;
				case 0x05:	// Set the speed/direction for the different motors
					PDdeactivate(); //Begin with deactivating PD-regulation
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
					p = SPI_Receive();
					d = SPI_Receive();
					setPD(p, d);
					break;
				case 0x07:	// Move forward with the specified speed
					PDdeactivate(); //Begin with deactivating PD-regulation
					driveForward();
					break;
				case 0x08:	// Move backward with the specified speed
					PDdeactivate(); //Begin with deactivating PD-regulation
					driveReverse();
					break;
				case 0x09:	// Rotate left with the specified speed
					PDdeactivate(); //Begin with deactivating PD-regulation
					rotateLeft();
					break;
				case 0x0A:	// Rotate right with the specified speed					
					PDdeactivate(); //Begin with deactivating PD-regulation
					rotateRight();
					break;
				case 0x0B:	// Close the claw
					gripClaw();
					break;
				case 0x0C:	// Open the claw
					releaseClaw();
					break;
				case 0x0D: // Stop the robot
					PDdeactivate(); //Begin with deactivating PD-regulation
					stopWheels();
					break;
				case 0x0E: // Set speed
					speed = SPI_Receive();
					maxSpeed = speed;
					break;
				case 0x0F:
					softTurnLeft();				
					break;
				case 0x10:
					softTurnRight();
					break;
				case 0x11:
					forwardToMiddle();
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
	sei();
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

void send_REQ() {
	PORTD |= (1<<REQ);
	_delay_us(1);
	PORTD &= ~(1<<REQ);
}