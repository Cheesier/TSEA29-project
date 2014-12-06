/*
 * algorithms.c
 *
 * Created: 2014-11-24 12:56:53
 *  Author: Jonathan
 */ 

#include "huvudenhet.h"
#include "pathList.h"

#define WALL_FRONT 0
#define WALL_BACK 1
#define WALL_LEFT 2
#define WALL_RIGHT 3

#define WALL_COUNT 4

#define DISTANCE_TO_WALL 34
#define DISTANCE_TO_WALL_FORWARD 30
#define DISTANCE_TO_WALL_BACKWARD 34
#define DISTANCE_TO_WALL_SIDES 30

#define DISTANCE_TO_MIDDLE 5


#define TRUE 1
#define FALSE 0

uint8_t reversing = 0;
uint8_t reversingOut = 0;
uint8_t currentState = STATE_PD;
uint8_t distanceForward, distanceBackward;
uint8_t useForward = TRUE;
uint8_t sectionType;
uint8_t turningStarted = 0;
uint16_t tape_data = 0;
uint8_t distance_data[4] = {0};
	
uint8_t counter = 0;
uint8_t old_intersection = FALSE;
	
uint8_t lock = 0;
uint8_t PD_activated = 0;
uint8_t middle_done = 0;
	
void resetRotation() {		
	turningStarted = 1;
	int dir = getDirection();
	switch(dir) {
		case RIGHT:
			motor_rotate_left_degrees(90);
			break;
		case LEFT:
			motor_rotate_right_degrees(90);
			break;
		default:
			setGyroDone();
			break;
	}
}


void updateSectionType(uint8_t* wallsInRange) {
	if (wallsInRange[WALL_FRONT]) {
		if (wallsInRange[WALL_LEFT]) {
			if (wallsInRange[WALL_RIGHT]) {
				sectionType = TYPE_DEAD_END;
				currentState = STATE_PD;
				motor_stop();
				if (reversing) {
					reversing = FALSE;
					motor_set_direction(1);	// Puts the robot in reverse-mode
				} else {
					reversing = TRUE;
					motor_set_direction(0);	// Puts the robot in reverse-mode
				}
				return;
			} else {
				sectionType = TYPE_TURN_RIGHT;
				currentState = STATE_ROTATE;
				return;
			}
		} else {
			if (wallsInRange[WALL_RIGHT]) {
				sectionType = TYPE_TURN_LEFT;
				currentState = STATE_ROTATE;
				return;
			} else {
				sectionType = TYPE_T_CROSS;
				currentState = STATE_ROTATE;
				return;
			}
		}
	} else {
		if (wallsInRange[WALL_LEFT]) {
			if (wallsInRange[WALL_RIGHT]) {
				sectionType = TYPE_CORRIDOR;
				currentState = STATE_ROTATE;
				return;
			} else {
				sectionType = TYPE_T_CROSS_RIGHT;
				currentState = STATE_ROTATE;
				return;
			}
		} else {
			if (wallsInRange[WALL_RIGHT]) {
				sectionType = TYPE_T_CROSS_LEFT;
				currentState = STATE_ROTATE;
				return;
			} else {
				sectionType = TYPE_INTERSECTION;
				currentState = STATE_ROTATE;
				return;
			}
		}
	}
}

int wallInRange(char distance, char distanceToWall) {
	return distance < distanceToWall;
}

// Returns TRUE if we're heading for the end goal
uint8_t checkReversing() {
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
		while(!isGyroDone());
		gyroModeOFF();				
		resetGyroDone();		
		
		
		if(!reversingOut) {			
			reversing = FALSE;	
			motor_set_direction(1);		
		}
	}
	return reversingOut;
}


// Handles the different intersections and turns
void startTurning() {
	turningStarted = 1;
	lcd_direction(getDirection());
	switch (sectionType) {
			
		case TYPE_TURN_LEFT:			
			motor_rotate_left_degrees(90);
			break;
			
		case TYPE_TURN_RIGHT:
			motor_rotate_right_degrees(90);
			break;
			
		case TYPE_T_CROSS:
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}*/
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);				
			}
			else if(getDirection() == RIGHT) {		// If we've already gone right
				motor_rotate_left_degrees(90);		// TODO: When we've returned to the intersection it should rotate to face the same way as the first time it entered the intersection
				setDirection(LEFT);				
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				popNode();
			}
			break;
			
		case TYPE_T_CROSS_LEFT:
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}*/
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				setDirection(FORWARD);
				setGyroDone();
			}
			else if(getDirection() == FORWARD) {	// If we've already gone forward
				motor_rotate_left_degrees(90);
				setDirection(LEFT);
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				popNode();
			}
			break;
			
		case TYPE_T_CROSS_RIGHT:
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}*/
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
			}
			else if(getDirection() == RIGHT) {		// If we've already gone forward
				setDirection(FORWARD);
				setGyroDone();
			}
			else if(getDirection() == FORWARD) {	// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				popNode();
			}
			break;
			
		case TYPE_INTERSECTION:
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}*/
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the crossroad
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
			}
			else if(getDirection() == RIGHT) {		// If we've already gone right
				setDirection(FORWARD);
				setGyroDone();
			}
			else if(getDirection() == FORWARD) {	// If we've already gone forward
				motor_rotate_left_degrees(90);
				setDirection(LEFT);
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				popNode();
			}
			break;
			
		default:
			currentState = STATE_PD;
			sectionType = TYPE_CORRIDOR;
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
	uint8_t wallsInRange[WALL_COUNT];
	
	wallsInRange[WALL_FRONT] = wallInRange(sensorData[0], DISTANCE_TO_WALL_FORWARD);
	wallsInRange[WALL_BACK] = wallInRange(sensorData[1], DISTANCE_TO_WALL_BACKWARD);
	wallsInRange[WALL_LEFT] = wallInRange(sensorData[2], DISTANCE_TO_WALL_SIDES);
	wallsInRange[WALL_RIGHT] = wallInRange(sensorData[3], DISTANCE_TO_WALL_SIDES);
	
	if(reversing == TRUE) {
		swapSensorDirections((uint8_t*)&wallsInRange);
		
	}
	
	lcd_state(currentState);
	
	
	switch (currentState) {		
		case STATE_PD:
			if (wallsInRange[WALL_FRONT] || !wallsInRange[WALL_LEFT] || !wallsInRange[WALL_RIGHT]) {
				PD_activated = 0;
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];				
				motor_stop();
				currentState = STATE_GOTO_MIDDLE;
			} else {
				if (!PD_activated) {
					PD_activated = 1;
					motor_set_speed(200);
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
				updateSectionType(wallsInRange);
				lcd_section_type(sectionType);
			} else {
				if(!lock) {
					motor_forward_to_middle();
					lock = 1;
				}
			}
			break;
		case STATE_ROTATE:
			if(reversing && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT) {
				currentState = STATE_ROTATE_RESET;
				break;
			}
			else if(old_intersection && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT){
				addNode();
				old_intersection = FALSE;
			}
			if (!turningStarted) {
				resetGyroDone();
				startTurning();
				turningStarted = 1;
			} else {
				if (isGyroDone()) {
					gyroModeOFF();
					lcd_section_type(TYPE_NONE);
					resetGyroDone();
					turningStarted = 0;
					currentState = STATE_FIND_WALLS;
				}
			}
			break;
		case STATE_FIND_WALLS:
			if (wallsInRange[WALL_LEFT] && wallsInRange[WALL_RIGHT]) {
				currentState = STATE_PD;
			} else {
				motor_set_speed(128);
				motor_go_forward();				
			}
			break;
		case STATE_ROTATE_RESET:
			if (!turningStarted) {
				resetGyroDone();
				resetRotation();
				turningStarted = 1;
				} else {
				if (isGyroDone()) {
					gyroModeOFF();
					resetGyroDone();
					turningStarted = 0;
					if(!reversingOut) {
						reversing = FALSE;
						motor_set_direction(1);
					}
					lcd_direction(getDirection());
					//_delay_ms(3000);
					old_intersection = TRUE;
					currentState = STATE_ROTATE;
				}
			}
			break;
		case STATE_FIND_OBJECT:		// enter state as soon as tape is found!
			motor_set_speed(32);
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
			motor_stop();
			//while(1); //
			break;
		default:
			break;
	}
}

