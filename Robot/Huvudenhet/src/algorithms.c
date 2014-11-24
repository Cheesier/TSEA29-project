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

#define TYPE_DEAD_END 0
#define TYPE_TURN_LEFT 1
#define TYPE_TURN_RIGHT 2
#define TYPE_T_CROSS 3
#define TYPE_T_CROSS_LEFT 4
#define TYPE_T_CROSS_RIGHT 5
#define TYPE_CROSSROAD 6
#define TYPE_CORRIDOR 7

int currentState = STATE_FIND_WALLS;
uint8_t distanceForward, distanceBackward;
int useForward;
int sectionType;
int turningStarted = 0;

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

char * checkWalls(char * distance) {
	char * wallsInRange;
	for(int i = 0; i < 4; i++) {
		wallsInRange[i] = wallInRange(distance[i]);
	}
	return wallsInRange;
}

/*
void resetGyro() {
	send_message_to(ADDR_SENSORENHET, 0x02, 0, 0); // Nollställa gyro
	resetGyroDone();
}*/

void startTurning() {
	switch (sectionType) {
		case TYPE_DEAD_END:
			send_message_to(ADDR_STYRENHET, 0x0D, 0, 0); // STOP
			break;
		case TYPE_TURN_LEFT:
			/*resetGyro();*/
			send_message_to(ADDR_SENSORENHET, 0x08, 0x01, 90); // Säg till efter 90 graders rotation
			send_message_to(ADDR_STYRENHET, 0x09, 0, 0); // Rotera till vänster
			break;
		case TYPE_TURN_RIGHT:
			/*resetGyro();*/
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
}

void interpretSensorData(char * sensorData) {
	char * wallsInRange = checkWalls(sensorData);
	switch (currentState) {
		case STATE_PD:
			if (wallsInRange[0] || !wallsInRange[2] || !wallsInRange[3]) {
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];
				useForward = distanceForward < distanceBackward;
				currentState = STATE_GOTO_MIDDLE;
			} else {
				send_message_to(ADDR_STYRENHET, 0x01, 0, 0); //PDForward()
			}
			break;
		case STATE_GOTO_MIDDLE:
			if (useForward) {
				if (distanceForward-sensorData[0] >= DISTANCE_TO_WALL/2) {
					updateSectionType(wallsInRange);
					currentState = STATE_ROTATE;
				} else {
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
		default:
			break;
	}
}