//
//  eventQ.h
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__eventQ__
#define __priorityQ__eventQ__

#include <stdio.h>
#include <queue>

using namespace std;

/* Define operator() for comparison class */
struct timeComparison {bool operator()(const event *lhs, const event *rhs) const;};

/* Define eventQ class */
class eventQ {
public:
	eventQ(); //constructor
	~eventQ(); //destructor
	
	/* Methods */
	void AddEvent(event * const theEvent);
	//Jeff has a Run() here that walks through events.
	
	/* Accessor methods */
	size_t Size() const; //size_t is a type able to represent the size of any object in bytes.
	//Empty
	double GetTime() const {return currentTime;}
	
	/* Methods */
	event * GetTop(); //Perhaps make private eventually.
	void PopTop();
	
private:
	priority_queue<event*, vector<event*>, timeComparison> iQ;
	double currentTime;
	
};

#endif /* defined(__priorityQ__eventQ__) */
