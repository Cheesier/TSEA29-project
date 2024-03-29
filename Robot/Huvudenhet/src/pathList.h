/*
 * pathList.h
 *
 * Created: 2014-11-27 11:49:52
 *  Author: Cavecanem
 */ 

#ifndef PATHLIST_H_
#define PATHLIST_H_

#define NOT_TURNED	0
#define LEFT		1
#define FORWARD		2
#define RIGHT		3
#define ERROR		33


struct intersection {
	struct intersection *previous;
	struct intersection *next;
	uint8_t direction;
};
	
struct pathList {
	struct intersection *first;
	struct intersection *last;	
};

//extern struct pathList path;

void initPathList();
void addNode();
void popNode();
void setDirection(uint8_t dir);
uint8_t getDirection();
void setNodesDone();

#endif /* PATHLIST_H_ */