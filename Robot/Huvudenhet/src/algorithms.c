/*
 * algorithms.c
 *
 * Created: 2014-11-24 12:56:53
 *  Author: Jonathan
 */ 

#include "algorithms.h"

#define DISTANCE_TO_WALL 40
#define STATE_PD 0
#define STATE_GOTO_MIDDLE 1
#define STATE_ROTATE 2
#define STATE_FIND_WALLS 3
#define STATE_FIND_OBJECT 4
#define STATE_START 5 //

#define TYPE_DEAD_END 0
#define TYPE_TURN_LEFT 1
#define TYPE_TURN_RIGHT 2
#define TYPE_T_CROSS 3
#define TYPE_T_CROSS_LEFT 4
#define TYPE_T_CROSS_RIGHT 5
#define TYPE_CROSSROAD 6
#define TYPE_CORRIDOR 7

int currentState = STATE_PD;
uint8_t distanceForward, distanceBackward;
int useForward;
int sectionType;
int turningStarted = 0;
uint16_t tape_data = 0;
uint16_t distance_data[4] = {0};

void updateSectionType(char* wallsInRange) {
	if (wallsInRange[0]) {
		if (wallsInRange[2]) {
			if (wallsInRange[3]) {
				sectionType = TYPE_DEAD_END;
				return;
			} else {
				sectionType = TYPE_TURN_RIGHT;
				return;
			}
		} else {
			if (wallsInRange[3]) {
				sectionType = TYPE_TURN_LEFT;
				return;
			} else {
				sectionType = TYPE_T_CROSS;
				return;
			}
		}
	} else {
		if (wallsInRange[2]) {
			if (wallsInRange[3]) {
				sectionType = TYPE_CORRIDOR;
				return;
			} else {
				sectionType = TYPE_T_CROSS_RIGHT;
				return;
			}
		} else {
			if (wallsInRange[3]) {
				sectionType = TYPE_T_CROSS_LEFT;
				return;
			} else {
				sectionType = TYPE_CROSSROAD;
				return;
			}
		}
	}
}

int wallInRange(char distance) {
	return distance < DISTANCE_TO_WALL;
}



/*
void resetGyro() {
	send_message_to(ADDR_SENSORENHET, 0x02, 0, 0); // Nollställa gyro
	resetGyroDone();
}*/

void startTurning() {
	switch (sectionType) {
		case TYPE_DEAD_END:
			motor_stop();
			//send_message_to(ADDR_STYRENHET, 0x0D, 0, 0); // STOP
			break;
		case TYPE_TURN_LEFT:
			/*resetGyro();*/
			send_message_to(ADDR_STYRENHET, 0x0D, 0, 0); // STOP
			_delay_ms(3000);
			send_message_to(ADDR_SENSORENHET, 0x08, 0x01, 90); // Säg till efter 90 graders rotation
			send_message_to(ADDR_STYRENHET, 0x09, 0, 0); // Rotera till vänster
			break;
		case TYPE_TURN_RIGHT:
			/*resetGyro();*/
			send_message_to(ADDR_STYRENHET, 0x0D, 0, 0); // STOP
			_delay_ms(3000);
			send_message_to(ADDR_SENSORENHET, 0x08, 0x01, 90); // Säg till efter 90 graders rotation
			send_message_to(ADDR_STYRENHET, 0x0A, 0, 0); // Rotera till vänster
			break;
		case TYPE_T_CROSS:
			/*Labyrintalgoritmen avgör vilket håll vi ska svänga åt*/
			break;
		case TYPE_T_CROSS_LEFT:
			/*Labyrintalgoritmen avgör vilket håll vi ska svänga åt*/
			break;
		case TYPE_T_CROSS_RIGHT:
			/*Labyrintalgoritmen avgör vilket håll vi ska svänga åt*/
			break;
		case TYPE_CROSSROAD:
			/*Labyrintalgoritmen avgör vilket håll vi ska svänga åt*/
			break;
		default:
			currentState = STATE_PD;
			break;
	}
	turningStarted = 1;
}

void interpretSensorData(char * sensorData) {
	char wallsInRange[4];
	
	for(int i = 0; i < 4; i++) {
		wallsInRange[i] = wallInRange(sensorData[i]);
	}
	
	switch (currentState) {
		case STATE_PD:
			if (wallsInRange[0] || !wallsInRange[2] || !wallsInRange[3]) {
				/*motor_stop();
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];
				useForward = distanceForward < distanceBackward;
				motor_stop();
				_delay_ms(3000);*/
				currentState = STATE_GOTO_MIDDLE;
			} else {				 
				motor_go_forward_pd();
				
				//check for tape!				
				send_message_to(ADDR_SENSORENHET, 0x07, 0, 0); // Asks the sensorenhet to send tape data
				// Might need delay
				read_message(ADDR_SENSORENHET);
				if(tape_data > 0 && tape_data != 0x07FF) {
					currentState = STATE_FIND_OBJECT;
				}
				
			}
			break;
		case STATE_GOTO_MIDDLE:
			if (useForward) {
				if (distanceForward-sensorData[0] >= DISTANCE_TO_WALL/2) {
					updateSectionType(wallsInRange);
					currentState = STATE_ROTATE;
				} else {
					motor_stop();
					_delay_ms(1000);
					send_message_to(ADDR_STYRENHET, 0x07, 0, 0); // driveForward()
				}
			} else {
				
				if (sensorData[1]-distanceBackward >= DISTANCE_TO_WALL/2) {
					updateSectionType(wallsInRange);
					currentState = STATE_ROTATE;
				} else {
					send_message_to(ADDR_STYRENHET, 0x07, 0, 0); // driveForward()
				}
			}
			break;
		case STATE_ROTATE:
			if (turningStarted) {
				if (isGyroDone()) {
					send_message_to(ADDR_STYRENHET, 0x0D, 0, 0); // STOP
					currentState = STATE_FIND_WALLS;
					_delay_ms(3000);
				}
			} else {
				startTurning();
			}
			break;
		case STATE_FIND_WALLS:
			if (wallsInRange[2] && wallsInRange[3]) {
				currentState = STATE_PD;
			} else {
				send_message_to(ADDR_STYRENHET, 0x07, 0, 0); // driveForward()
			}
			break;
		case STATE_FIND_OBJECT:		// enter state as soon as tape is found!
			motor_set_speed(0x20);	// going with speed 32, should continue with pdForward()
			motor_go_forward_pd();	
					
			//Continue to update tape data
			send_message_to(ADDR_SENSORENHET, 0x07, 0, 0); // Asks the sensorenhet to send tape data
			// Might need delay
			read_message(ADDR_SENSORENHET);
			//if(tape_data == 0x07FF) { // Assumes that this switch-case statement loops somehow
			if(tape_data == 0x0000) {
				motor_stop();
				_delay_us(50);
				motor_claw_close();
				currentState = STATE_START;
			}
			break;
		case STATE_START:
			motor_stop();
			break;
		default:
			break;
	}
}