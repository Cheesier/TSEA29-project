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
void startTurning() {
	turningStarted = 1;
	lcd_set_cursor(4,2);
	lcd_clear();
	switch (sectionType) {
		
		case TYPE_DEAD_END:
			motor_stop();
			printf("Dead end");
			currentState = STATE_DONE;
			/*motor_stop();
			_delay_ms(1000);
			reversing = TRUE;
			motor_set_direction(0);	// Puts the robot in reverse-mode
			currentState = STATE_PD;	
			// TODO: Back until we come to the last intersection*/
			break;
			
		case TYPE_TURN_LEFT:
			motor_stop();
			printf("Left turn");
			currentState = STATE_DONE;			
			/*motor_stop();			
			_delay_ms(3000);
			motor_rotate_left_degrees(90);*/
			break;
			
		case TYPE_TURN_RIGHT:					
			motor_stop();
			printf("Right turn");
			currentState = STATE_DONE;
			/*motor_stop();			
			_delay_ms(3000);
			motor_rotate_right_degrees(90);*/
			break;
			
		case TYPE_T_CROSS:
			motor_stop();
			printf("T-cross");
			currentState = STATE_DONE;	
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == RIGHT) {		// If we've already gone right
				motor_rotate_left_degrees(90);		// TODO: When we've returned to the intersection it should rotate to face the same way as the first time it entered the intersection
				setDirection(LEFT);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				currentState = STATE_PD;
				popNode();
			}*/
			break;
			
		case TYPE_T_CROSS_LEFT:
			motor_stop();
			printf("T-cross left");
			currentState = STATE_DONE;
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				setDirection(FORWARD);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == FORWARD) {	// If we've already gone forward
				motor_rotate_left_degrees(90);
				setDirection(LEFT);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads				
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				currentState = STATE_PD;
				popNode();
			}*/
			break;
			
		case TYPE_T_CROSS_RIGHT:
			motor_stop();
			printf("T-cross right");
			currentState = STATE_DONE;
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the intersection
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == RIGHT) {		// If we've already gone forward				
				setDirection(FORWARD);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == FORWARD) {	// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				currentState = STATE_PD;
				popNode();
			}*/
			break;
			
		case TYPE_CROSSROAD:
			motor_stop();
			printf("Intersection");
			currentState = STATE_DONE;			
			/*if(checkReversing()) {
				popNode();
				currentState = STATE_FIND_WALLS;
				break;
			}
			if(getDirection() == NOT_TURNED) {		// If it's the first time in the crossroad
				motor_rotate_right_degrees(90);
				setDirection(RIGHT);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == RIGHT) {		// If we've already gone right
				setDirection(FORWARD);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == FORWARD) {	// If we've already gone forward				
				motor_rotate_left_degrees(90);
				setDirection(LEFT);
				currentState = STATE_FIND_WALLS;
			}
			else if(getDirection() == LEFT) {		// If we've visited all roads
				reversing = TRUE;
				motor_set_direction(0);	// Puts the robot in reverse-mode
				currentState = STATE_PD;
				popNode();
			}*/
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
	
	/*for(int i = 0; i < 4; i++) {
		wallsInRange[i] = wallInRange(sensorData[i], DISTANCE_TO_WALL);
	}*/
	if(reversing == TRUE) {
		swapSensorDirections((uint8_t*)&wallsInRange);
		
	}
	lcd_set_cursor(0,1);
	switch (currentState) {		
		case STATE_PD:
			lcd_set_cursor(4,1);
			printf("STATE_PD");
			if (wallsInRange[0] || !wallsInRange[2] || !wallsInRange[3]) {
				//motor_stop();
				distanceForward = sensorData[0];
				distanceBackward = sensorData[1];
				/*useForward = distanceForward < distanceBackward;
				motor_stop();
				_delay_ms(3000);*/				
				motor_stop();
				/*motor_set_speed(64);
				motor_go_forward();*/
				currentState = STATE_GOTO_MIDDLE;
			} else {
				motor_set_speed(200);
				motor_go_forward_pd();
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
				lcd_clear();
				lcd_set_cursor(4,1);
				printf("DONE");
				middle_done = 0;
				lock = 0;
				motor_stop();
				updateSectionType(wallsInRange);
				currentState = STATE_ROTATE;
			} else {
				if(!lock) {
					lcd_set_cursor(4,1);
					printf("GO_TO_MIDDLE");
					motor_stop();
					_delay_ms(2000);
					motor_forward_to_middle();
					lock = 1;
				}
				lcd_set_cursor(4,1);
				printf("%u", counter++);
				_delay_ms(1);
			}
			break;
		case STATE_ROTATE:
			lcd_set_cursor(4,1);
			printf("ROTATE");
			if (turningStarted) {
				if (isGyroDone()) {
					turningStarted = 0;
					motor_stop();					
					currentState = STATE_FIND_WALLS;
					_delay_ms(3000);
				}
			} else {
				startTurning();
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