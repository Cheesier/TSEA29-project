/*
 * algorithms.c
 *
 * Created: 2014-11-24 12:56:53
 *  Author: Jonathan
 */ 

#include "huvudenhet.h"
#include "pathList.h"

#define DISTANCE_TO_WALL 34
#define DISTANCE_TO_WALL_FORWARD 30
#define DISTANCE_TO_WALL_BACKWARD 34
#define DISTANCE_TO_WALL_SIDES 30

#define DISTANCE_TO_MIDDLE 5
#define STATE_PD 0
#define STATE_GOTO_MIDDLE 1
#define STATE_ROTATE 2
#define STATE_FIND_WALLS 3
#define STATE_FIND_OBJECT 4
#define STATE_DONE 5 //

#define TYPE_DEAD_END 0
#define TYPE_TURN_LEFT 1
#define TYPE_TURN_RIGHT 2
#define TYPE_T_CROSS 3
#define TYPE_T_CROSS_LEFT 4
#define TYPE_T_CROSS_RIGHT 5
#define TYPE_CROSSROAD 6
#define TYPE_CORRIDOR 7

#define TRUE 1
#define FALSE 0

int reversing = 0;
int reversingOut = 0;
int currentState = STATE_PD;
uint8_t distanceForward, distanceBackward;
int useForward = TRUE;
int sectionType;
int turningStarted = 0;
uint16_t tape_data = 0;
uint8_t distance_data[4] = {0};
	
int counter = 0;
	
int lock = 0;
int PD_activated;

int middle_done = 0;
	

void updateSectionType(uint8_t* wallsInRange) {
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

int wallInRange(char distance, char distanceToWall) {
	return distance < distanceToWall;
}



/*
void resetGyro() {
	send_message_to(ADDR_SENSORENHET, 0x02, 0, 0); // Nollställa gyro
	resetGyroDone();
}*/

// Returns TRUE if we're heading for the end goal
int checkReversing() {
	if(reversing) {
		int dir = getDirection();
		switch(dir) {
			case RIGHT:
				motor_rotate_right_degrees(90);
				break;
			case LEFT:
				motor_rotate_left_degrees(90);
				break;
			default:
				break;
		}
		if(!reversingOut) {
			reversing = FALSE;	
			motor_set_direction(1);		
		}
	}
	return reversingOut;
}

// Handles the different intersections and turns
void continueTurning() {
	turningStarted = 1;
	lcd_clear();
	lcd_set_cursor(4,2);
	switch (sectionType) {
		
		case TYPE_DEAD_END:
			motor_stop();
			printf("Dead end");
			motor_rotate_right();
			break;
			
		case TYPE_TURN_LEFT:
			printf("Left turn");
			motor_rotate_left();
			break;
			
		case TYPE_TURN_RIGHT:
			printf("Right turn");
			motor_rotate_right();
			break;
			
		case TYPE_T_CROSS:
			motor_stop();
			printf("T-cross");
			motor_rotate_right();
			break;
			
		case TYPE_T_CROSS_LEFT:
			motor_stop();
			printf("T-cross left");
			motor_rotate_left();
			break;
			
		case TYPE_T_CROSS_RIGHT:
			motor_stop();
			printf("T-cross right");
			motor_rotate_right();
			break;
			
		case TYPE_CROSSROAD:
			motor_stop();
			printf("Intersection");		
			motor_rotate_right();
			break;
			
		default:
			currentState = STATE_PD;
			break;
	}
}

// Handles the different intersections and turns
void startTurning() {
	turningStarted = 1;
	lcd_clear();
	lcd_set_cursor(4,2);
	switch (sectionType) {
		
		case TYPE_DEAD_END:
			printf("Dead end");
			motor_stop();
			_delay_ms(1000);
			reversing = TRUE;
			motor_set_direction(0);	// Puts the robot in reverse-mode
			currentState = STATE_PD;	
			// TODO: Back until we come to the last intersection
			break;
			
		case TYPE_TURN_LEFT:
			printf("Left turn");
			motor_rotate_left_degrees(90);
			break;
			
		case TYPE_TURN_RIGHT:
			printf("Right turn");
			motor_rotate_right_degrees(90);
			break;
			
		case TYPE_T_CROSS:
			motor_stop();
			printf("T-cross");
			motor_rotate_right_degrees(90);
			break;
			
		case TYPE_T_CROSS_LEFT:
			motor_stop();
			printf("T-cross left");
			motor_rotate_left_degrees(90);
			break;
			
		case TYPE_T_CROSS_RIGHT:
			motor_stop();
			printf("T-cross right");
			motor_rotate_right_degrees(90);
			break;
			
		case TYPE_CROSSROAD:
			motor_stop();
			printf("Intersection");
			motor_rotate_right_degrees(90);
			break;
			
		default:
			currentState = STATE_PD;
			break;
	}
	turningStarted = 1;
}


void swapSensorDirections(uint8_t *sensorData) {
	char temp = sensorData[0];
	sensorData[0] = sensorData[1];
	sensorData[1] = temp;
}

void interpretSensorData(uint8_t *sensorData) {
	uint8_t wallsInRange[4];
	
	wallsInRange[0] = wallInRange(sensorData[0], DISTANCE_TO_WALL_FORWARD);
	wallsInRange[1] = wallInRange(sensorData[1], DISTANCE_TO_WALL_BACKWARD);
	wallsInRange[2] = wallInRange(sensorData[2], DISTANCE_TO_WALL_SIDES);
	wallsInRange[3] = wallInRange(sensorData[3], DISTANCE_TO_WALL_SIDES);
	
	if(reversing == TRUE) {
		swapSensorDirections((uint8_t*)&wallsInRange);
		
	}
	lcd_clear();
	switch (currentState) {		
		case STATE_PD:
			lcd_set_cursor(4,1);
			printf("STATE_PD");
			if (wallsInRange[0] || !wallsInRange[2] || !wallsInRange[3]) {
				PD_activated = 0;
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];				
				motor_stop();
				currentState = STATE_GOTO_MIDDLE;
			} else {
				if (!PD_activated) {
					PD_activated = 1;
					motor_set_speed(128);
					motor_go_forward_pd();
				}
				//check for tape!
				if(!reversingOut && tape_data > 0 && tape_data != 0x07FF) {
					//currentState = STATE_FIND_OBJECT;
				}
				else if(reversingOut && tape_data == 0x07FF) {
					//currentState = STATE_DONE;
				}
				
			}
			break;
		case STATE_GOTO_MIDDLE:
			if (middle_done) {
				middle_done = 0;
				lock = 0;
				lcd_set_cursor(6,2);
				printf("DONE!");
				updateSectionType(wallsInRange);
				currentState = STATE_ROTATE;
			} else {
				if(!lock) {
					lcd_set_cursor(4,1);
					printf("GO_TO_MIDDLE");
					motor_forward_to_middle();
					lock = 1;
				}
			}
			break;
		case STATE_ROTATE:
			lcd_set_cursor(4,1);
			printf("ROTATE");
			if (!turningStarted) {
				startTurning();
				turningStarted = 1;
			} else {
			printf("%3u", counter++);
				if (isGyroDone()) {
					resetGyroDone();
					turningStarted = 0;
					currentState = STATE_FIND_WALLS;
				} else {
					continueTurning();
				}
			}
			break;
		case STATE_FIND_WALLS:
			lcd_set_cursor(4,1);
			printf("FIND_WALLS");
			if (wallsInRange[2] && wallsInRange[3]) {
				currentState = STATE_PD;
			} else {
				motor_go_forward();				
			}
			break;
		case STATE_FIND_OBJECT:		// enter state as soon as tape is found!
			motor_set_speed(0x20);	// setting speed to 32, should continue with pdForward()
			motor_go_forward_pd();	
					
			//Continue to update tape data
			//if(tape_data == 0x07FF) { // Assumes that this switch-case statement loops somehow
			if(tape_data == 0x0000) {
				motor_stop();
				_delay_us(50);
				motor_claw_close();
				reversing = TRUE;
				reversingOut = TRUE;				
				currentState = STATE_FIND_WALLS;
			}
			break;
		case STATE_DONE:
			lcd_set_cursor(4,1);
			printf("STATE DONE");
			motor_stop();
			//while(1); //
			break;
		default:
			break;
	}
}