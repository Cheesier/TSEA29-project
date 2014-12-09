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
#define DISTANCE_TO_WALL_SIDES 34

#define DISTANCE_TO_MIDDLE 5


uint8_t reversing = FALSE;
uint8_t reversingOut = FALSE;
uint8_t currentState = STATE_PD;
uint8_t distanceForward, distanceBackward;
uint8_t useForward = TRUE;
uint8_t sectionType;
uint8_t turningStarted = FALSE;
uint16_t tape_data = 0;
uint8_t distance_data[4] = {0};
	
uint8_t counter = 0;
uint8_t old_intersection = FALSE;
	
uint8_t lock = FALSE;
uint8_t lock_wall = FALSE;
uint8_t PD_activated = FALSE;
uint8_t middle_done = FALSE;

uint8_t extra_iteration = FALSE;

// Resets the rotation to how it entered the intersection the first time.
void resetRotation() {		
	turningStarted = TRUE;
	uint8_t dir = getDirection();
	switch(dir) {
		case RIGHT:
			motor_rotate_right_degrees(90);
			break;
		case LEFT:
			motor_rotate_left_degrees(90);
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
				motor_stop();
				if (reversing) {
					currentState = STATE_DONE;
				} else {
					motor_set_direction(FALSE);	// Puts the robot in reverse-mode
					currentState = STATE_PD;
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
				currentState = STATE_PD;
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

// Handles the different intersections and turns
void startTurning() {
	turningStarted = TRUE;
	if(reversingOut && !(TYPE_TURN_LEFT || TYPE_TURN_RIGHT)) {
		popNode();
		setGyroDone();
		return;
	}
	switch (sectionType) {
			
		case TYPE_TURN_LEFT:			
			motor_rotate_left_degrees(90);
			break;
			
		case TYPE_TURN_RIGHT:
			motor_rotate_right_degrees(90);
			break;
			
		case TYPE_T_CROSS:
			lcd_direction(getDirection());
			
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
			}
			else if(getDirection() == RIGHT) {		// If we've already gone right
				motor_rotate_left_degrees(90);		
				setDirection(LEFT);
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				motor_set_direction(FALSE);	// Puts the robot in reverse-mode
				popNode();
				setGyroDone();
			}
			break;
			
		case TYPE_T_CROSS_LEFT:
			lcd_direction(getDirection());
			
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				setDirection(FORWARD);
				setGyroDone();
			}
			else if(getDirection() == FORWARD) {	// If we've already gone forward
				motor_rotate_left_degrees(90);
				setDirection(LEFT);
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				motor_set_direction(FALSE);			// Puts the robot in reverse-mode
				popNode();
				setGyroDone();
			}
			break;
			
		case TYPE_T_CROSS_RIGHT:
			lcd_direction(getDirection());
			
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
			}
			else if(getDirection() == RIGHT) {		// If we've already gone forward
				setDirection(FORWARD);
				setGyroDone();
			}
			else if(getDirection() == FORWARD) {	// If we've visited all roads
				motor_set_direction(FALSE);			// Puts the robot in reverse-mode
				popNode();
				setGyroDone();
			}
			break;
			
		case TYPE_INTERSECTION:
			lcd_direction(getDirection());
			
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
				motor_set_direction(FALSE);			// Puts the robot in reverse-mode
				popNode();
				setGyroDone();
			}
			break;
			
		default:
			currentState = STATE_PD;
			sectionType = TYPE_CORRIDOR;
			break;
	}
}

// Counts and returns the number of bits set in the tape_data
uint8_t countBits(uint16_t number) {
	uint8_t bits = 0;
	
	for(int i = 0; i < 11; i++) {
		if ((number & 1) == 1)
			bits++;
		number >>= 1;
	}
	
	return bits;
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
	
	if(reversing) {
		swapSensorDirections((uint8_t*)&wallsInRange);		
	}
	
	lcd_state(currentState);
	
	
	switch (currentState) {		
		case STATE_PD:
			if (wallsInRange[WALL_FRONT] || !wallsInRange[WALL_LEFT] || !wallsInRange[WALL_RIGHT]) {
				PD_activated = FALSE;
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];				
				motor_stop();
				currentState = STATE_GOTO_MIDDLE;
			} else {
				if (!PD_activated) {
					PD_activated = TRUE;
					motor_set_speed(150);
					motor_go_forward_pd();
				}
				//check for tape!
				if(!reversingOut && tape_data > 0 && tape_data != 0x07FF) {
					currentState = STATE_FIND_OBJECT;
					motor_stop();
					_delay_ms(100);
				}
				/*else if(reversingOut && tape_data == 0x07FF) {
					//currentState = STATE_DONE;
				}*/
				
			}
			break;
		case STATE_GOTO_MIDDLE:
			cli();
			motor_set_speed(128);
			motor_go_forward();		
			if (!reversing)
				_delay_ms(100);
			if (reversing)
				_delay_ms(160);
			motor_stop();
			sei();
			
			updateSectionType(wallsInRange);
			lcd_section_type(sectionType);
			/*if (middle_done) {				
				middle_done = FALSE;
				lock = FALSE;
				updateSectionType(wallsInRange);
				lcd_section_type(sectionType);
			} else {
				if(!lock) {					
					motor_forward_to_middle();
					lock = TRUE;
				}
				_delay_us(1);
			}*/
			break;
		case STATE_ROTATE:
			if (!turningStarted) {
				checkpoints[0] = TRUE;
				if(reversing && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT) {
					checkpoints[1] = TRUE;
					currentState = STATE_ROTATE_RESET;
					break;
				}
				else if(!old_intersection && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT){
					checkpoints[2] = TRUE;
					addNode();
				}
				old_intersection = FALSE;
				resetGyroDone();
				startTurning();
			} else {
				checkpoints[3] = TRUE;
				if (isGyroDone()) {
					lcd_section_type(TYPE_NONE);
					resetGyroDone();
					turningStarted = FALSE;
					currentState = STATE_FIND_WALLS;
				}
			}
			break;
		case STATE_FIND_WALLS:
			setDistanceMode();
			if (wallsInRange[WALL_LEFT] && wallsInRange[WALL_RIGHT]) {
				lock_wall = FALSE;
				currentState = STATE_PD;
			} else if(!lock_wall) {
				lock_wall = TRUE;
				motor_set_speed(150);
				motor_go_forward();				
			} else {
				_delay_us(1);
			}
			break;
		case STATE_ROTATE_RESET:
			if (extra_iteration) { //To wait for a new sensor-data input
				extra_iteration = FALSE;
				updateSectionType(wallsInRange);
				lcd_section_type(sectionType);
				lcd_direction(getDirection());
			}
			else if (!turningStarted) {
				resetGyroDone();
				resetRotation();
			} 
			else {
				if (isGyroDone()) {
					resetGyroDone();
					
					turningStarted = FALSE;
					if(!reversingOut) {
						motor_set_direction(TRUE);
						swapSensorDirections((uint8_t*)&wallsInRange);
					}
					lcd_direction(getDirection());
					
					old_intersection = TRUE;
					extra_iteration = TRUE;
					_delay_ms(60);
				}
			}
			break;
		case STATE_FIND_OBJECT:		// enter state as soon as tape is found!
			motor_set_speed(90);
			motor_go_forward_pd();	
					
			//Continue to update tape data
			//if(tape_data == 0x07FF) { // Assumes that this switch-case statement loops somehow
			if(countBits(tape_data) >= 9) {
				motor_stop();
				_delay_us(50);
				motor_claw_close();
				motor_set_direction(FALSE);
				_delay_ms(150);
				motor_set_speed(150);
				reversingOut = TRUE;
				currentState = STATE_PD;
			} else if(tape_data == 0) {
				motor_set_speed(150);
				currentState = STATE_PD;				
			}
			break;
		case STATE_DONE:
			motor_stop();
			break;
		default:
			break;
	}
}