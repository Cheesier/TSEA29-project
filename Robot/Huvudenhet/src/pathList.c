/*
 * pathList.c
 *
 * Created: 2014-11-27 11:49:41
 *  Author: Cavecanem
 */ 

#include "huvudenhet.h"

static struct pathList path;

uint8_t nodeCounter = 0;

// Initializes the list
void initPathList(void) {
	nodeCounter = 0;
	path.first = NULL;
	path.last = NULL;
}

// Adds a new intersection to the list
void addNode(void) {
	nodeCounter += 1;
	lcd_nodes(nodeCounter);
	struct intersection *node = malloc(sizeof(struct intersection));
	node->next = NULL;
	node->direction = NOT_TURNED;
	
	if(path.first != NULL) {
		node->previous = path.last;
		path.last->next = node;
		path.last = node;
	}
	else {
		node->previous = NULL;
		path.first = node;
		path.last = node;
	}
}

// Remove the last intersection
void popNode(void) {
	nodeCounter -= 1;
	lcd_nodes(nodeCounter);
	if(path.last != NULL) {
		struct intersection* section_to_delete = path.last;
		path.last = path.last->previous;
		
		if (path.last != NULL) {
			path.last->next = NULL;
		}
		
		free(section_to_delete);
	}
}

// Sets the direction we turned in the last intersection
void setDirection(uint8_t dir) {
	if(path.last != NULL) {
		path.last->direction = dir;
	}
}

// Returns the direction we turned in the last intersection
uint8_t getDirection(void) {
	if(path.last != NULL)
		return path.last->direction;
	else
		return DONE;
}