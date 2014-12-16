/*
 * algorithms.c
 *
 * Created: 2014-11-24 12:56:53
 *  Author: Jonathan
 */ 

#include "algorithms.h"
#include "huvudenhet.h"
#include "pathList.h"
#include <util/atomic.h>

#define WALL_FRONT 0
#define WALL_BACK 1
#define WALL_LEFT 2
#define WALL_RIGHT 3

#define STATE_GOTO_MIDDLE 1 // Doesn't seem to find it if it isn't here :s TODO

#define DISTANCE_TO_WALL_FORWARD 25
#define DISTANCE_TO_WALL_BACKWARD 25
#define DISTANCE_TO_WALL_SIDES 40

#define DISTANCE_TO_MIDDLE 5

#define TAPE_SPEED 115
#define PD_SPEED 130 //130
#define GO_TO_MIDDLE_SPEED 128

uint8_t reversing = FALSE;
uint8_t reversingOut = FALSE;
uint8_t resetRotateDone = FALSE;
uint8_t currentState = STATE_FIND_WALLS;
uint8_t distanceForward, distanceBackward;
uint8_t useForward = TRUE;
uint8_t sectionType;
uint8_t turningStarted = FALSE;
uint16_t tape_data = 0;
uint8_t distance_data[4] = {0};
uint8_t findingObject = FALSE;
uint8_t wallsInRange[WALL_COUNT];
	
uint8_t counter = 0;
uint8_t old_intersection = FALSE;
uint8_t in_a_dead_end = FALSE;
	
uint8_t lock = FALSE;
uint8_t lock_wall = FALSE;
uint8_t PD_activated = FALSE;
uint8_t middle_done = FALSE;
uint8_t update_section = FALSE;

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
		case DONE:
			currentState = STATE_DONE;
			break;
		default:
			setGyroDone();
			break;
	}
}

// Checks what kind of intersection it is with the given distancesensors
void updateSectionType(uint8_t* wallsInRange) {
	if (wallsInRange[WALL_FRONT]) {
		if (wallsInRange[WALL_LEFT]) {
			if (wallsInRange[WALL_RIGHT]) {
				sectionType = TYPE_DEAD_END;
				motor_stop();
				if (reversing) {
					update_section = TRUE;
					return;
				} else {
					motor_set_direction(DIR_REVERSE);		// Puts the robot in reverse-mode
					update_section = TRUE;
					in_a_dead_end = TRUE;
					_delay_ms(60);					
					return;
					//currentState = STATE_PD;
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

// Check if a wall is in a given interval 
int wallInRange(char distance, char distanceToWall) {
	return distance < distanceToWall;
}

// Handles the different intersections and turns
void startTurning() {
	turningStarted = TRUE;
	if(reversingOut && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT) {
		popNode();
		setGyroDone();
		setDistanceModeOn();
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
				motor_set_direction(DIR_REVERSE);	// Puts the robot in reverse-mode
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
				motor_set_direction(DIR_REVERSE);	// Puts the robot in reverse-mode
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
				motor_set_direction(DIR_REVERSE);	// Puts the robot in reverse-mode
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
				motor_set_direction(DIR_REVERSE);	// Puts the robot in reverse-mode
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

// Swaps the front and back sensors data
void swapSensorDirections(uint8_t *sensorData) {
	char temp = sensorData[0];
	sensorData[0] = sensorData[1];
	sensorData[1] = temp;
}

//The maze algorithm 
void interpretSensorData(uint8_t *sensorData) { 
	//uint8_t wallsInRange[WALL_COUNT];	
	wallsInRange[WALL_FRONT] = wallInRange(sensorData[0], DISTANCE_TO_WALL_FORWARD);
	wallsInRange[WALL_BACK] = wallInRange(sensorData[1], DISTANCE_TO_WALL_BACKWARD);
	wallsInRange[WALL_LEFT] = wallInRange(sensorData[2], DISTANCE_TO_WALL_SIDES);
	wallsInRange[WALL_RIGHT] = wallInRange(sensorData[3], DISTANCE_TO_WALL_SIDES);
	
	if(reversing) {
		swapSensorDirections((uint8_t*)&wallsInRange);
	}
	
	if(update_section) {
		update_section = FALSE;
		updateSectionType(wallsInRange);
		lcd_section_type(sectionType);
		lcd_direction(getDirection());		
	}
	
	lcd_state(currentState);
	lcd_reversing();
		
	switch (currentState) {
		// STATE_PD
		// In this state the robots moves forward with PD-regulation activated
		// STATE_PD ends when we get a wall in front of us, or we don't have a wall to the right or to the left of us (in a given interval)
		// When it notices a wall in front or a wall to the side disappear it sets currentState to GO_TO_MIDDLE
		case STATE_PD:
			if (in_a_dead_end) {
				if (!PD_activated) {
					PD_activated = TRUE;
					motor_set_speed(PD_SPEED);
					motor_go_forward_pd();								
				}				
				in_a_dead_end = FALSE;
			} else if (wallsInRange[WALL_FRONT] || !wallsInRange[WALL_LEFT] || !wallsInRange[WALL_RIGHT]) {
				PD_activated = FALSE;
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];				
				//motor_stop();
				currentState = STATE_GOTO_MIDDLE;
			} else {
				if (!PD_activated) {
					PD_activated = TRUE;
					motor_set_speed(PD_SPEED);
					motor_go_forward_pd();
				}
				//check for tape!
				if(!reversing && tape_data > 0 && tape_data != 0x07FF) {
					PD_activated = FALSE;
					currentState = STATE_FIND_OBJECT;
					//motor_set_pd(50,220);					
					motor_stop();
					_delay_ms(50);
					motor_go_forward_pd();			
				}
				/*else if(reversingOut && tape_data == 0x07FF) {
					//currentState = STATE_DONE;
				}*/
				
			}
			break;
		// STATE_GOTO_MIDDLE
		// Used to make the robot move into the middle of an intersection when we have to turn
		// The motors is turned on without PD-regulation and then turned off after a set time
		// The function is handled by Styrenheten. A message is sent to Styrenheten to initiate the function and an interrupt is triggerd in Huvudenheten when it's done
		// Time based and is affected by the speed at which the robots moves in corridors (thanks to wheels still having momentum when turned off)
		// When done sets currentsState to STATE_ROTATE
		case STATE_GOTO_MIDDLE:
			ATOMIC_BLOCK(ATOMIC_FORCEON) {
				motor_set_speed(GO_TO_MIDDLE_SPEED);
				motor_go_forward();		
				if (!reversing)
					//_delay_ms(80);		//100 worked before
					_delay_ms(120);
				if (reversing)
					//_delay_ms(90);
					_delay_ms(150);
				motor_stop();
			}	
			update_section = TRUE;

			break;
		// STATE_ROTATE
		// Used to check how to rotate and start to rotate the robot when the right rotation is found
		// Checks if the intersection is an old intersection or a new one. If new it adds a new node and if it's an old node it pops it. 
		// When done sets currentState to STATE_ROTATE_RESET
		case STATE_ROTATE:
			if (!turningStarted) {				
				checkpoints[0] = TRUE;
				if(reversing && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT && !resetRotateDone) {
					checkpoints[1] = TRUE;
					currentState = STATE_ROTATE_RESET;
					break;
				}
				else if(!old_intersection && sectionType != TYPE_TURN_LEFT && sectionType != TYPE_TURN_RIGHT){
					checkpoints[2] = TRUE;
					addNode();
				}
				resetRotateDone = FALSE;
				old_intersection = FALSE;
				resetGyroDone();				
				startTurning();				
			} else {
				checkpoints[3] = TRUE;
				if (isGyroDone()) {
					lcd_section_type(TYPE_NONE);
					resetGyroDone();
					setDistanceModeOn(); //TODO
					turningStarted = FALSE;
					currentState = STATE_FIND_WALLS;
				}
			}
			break;
		//
		case STATE_FIND_WALLS:
			ATOMIC_BLOCK(ATOMIC_FORCEON) {				
				if (wallsInRange[WALL_LEFT] && wallsInRange[WALL_RIGHT]) {
					lock_wall = FALSE;
					currentState = STATE_PD;
				} else if(!lock_wall) {
					lock_wall = TRUE;
					motor_set_speed(PD_SPEED);
					motor_go_forward();
				} else {
					_delay_ms(1);
				}
			}
			break;
		case STATE_ROTATE_RESET:
			if (!turningStarted) {
				resetGyroDone();
				resetRotation();
			} 
			else {
				if (isGyroDone()) {
					resetGyroDone();
					
					turningStarted = FALSE;
					if(!reversingOut) {
						motor_set_direction(DIR_FORWARD);
						swapSensorDirections((uint8_t*)&wallsInRange);
					} else {
						resetRotateDone = TRUE;
					}
					lcd_direction(getDirection());
					
					old_intersection = TRUE;
					//extra_iteration = TRUE;
					update_section = TRUE;
					_delay_ms(200);
				}
			}
			break;
		case STATE_FIND_OBJECT:		// enter state as soon as tape is found!			
			//cli();
			ATOMIC_BLOCK(ATOMIC_FORCEON) {				
				findingObject = TRUE;			
				motor_set_pd(255,0);
				motor_set_speed(TAPE_SPEED);

				motor_go_forward_pd();	
					
				//Continue to update tape data
				if(countBits(tape_data) >= 6) {
					motor_stop();
					_delay_ms(100);
					motor_claw_close();
					motor_set_direction(DIR_REVERSE);
					_delay_ms(150);
					motor_set_speed(PD_SPEED);
					motor_reset_pd();
					findingObject = FALSE;
					reversingOut = TRUE;
					currentState = STATE_PD;
				} else if(tape_data == 0) {
					motor_set_speed(PD_SPEED);
					findingObject = FALSE;
					motor_reset_pd();
					currentState = STATE_PD;
				}
			}
			//sei();
			break;
		case STATE_DONE:
			motor_stop();
			motor_claw_open();
			break;
		default:
			break;
	}
}