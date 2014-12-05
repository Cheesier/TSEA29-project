/*
 * pathList.c
 *
 * Created: 2014-11-27 11:49:41
 *  Author: Cavecanem
 */ 

#include "huvudenhet.h"

struct pathList path;

// Initializes the list
void initPathList() {
	path.first = NULL;
	path.last = NULL;
}

// Adds a new intersection to the list
void addNode() {
	struct intersection node;
	node.next = NULL;
	
	if(path.first != NULL) {
		node.previous = path.last;
		path.last->next = &node;
	}
	else {
		node.previous = NULL;		
		path.first = &node;	
	}
}

// Remove the last intersection
void popNode() {
	if(path.last != NULL) {
		path.last = path.last->previous;	// Sets the last node to the previous node
		if(path.last->previous != NULL)
			path.last->next = NULL;			// Sets the previous last node to NULL, only if that node isn't NULL (if it is the first)
	}
}

// Sets the direction we turned in the last intersection
void setDirection(int dir) {
	if(path.last != NULL) {
		path.last->direction = dir;		
	}
}

// Returns the direction we turned in the last intersection
int getDirection() {
	if(path.last != NULL)
		return path.last->direction;
	else
		return NOT_TURNED;
}