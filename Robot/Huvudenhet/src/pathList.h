/*
 * pathList.h
 *
 * Created: 2014-11-27 11:49:52
 *  Author: Cavecanem
 */ 

#ifndef PATHLIST_H_
#define PATHLIST_H_

#define LEFT		0
#define FORWARD		1
#define RIGHT		2


struct intersection {
	struct intersection *previous;
	struct intersection *next;
	int direction;
};
	
struct pathList {
	struct intersection *first;
	struct intersection *last;	
};
	
	

#endif /* PATHLIST_H_ */