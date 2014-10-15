//
//  events.h
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__events__
#define __priorityQ__events__

#include <stdio.h>
#include "event.h"

/////////////////////
/////////////////////

class Death : public event {
public:
	Death(const double Time); //constructor
	~Death(); //destructor
	
	/* Methods */
	void Execute();
};


/////////////////////
/////////////////////

class HivTest : public event {
public:
	HivTest(const double Time); //constructor
	~HivTest(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	//Some private stuff
	
};

/////////////////////
/////////////////////

class Cd4Test : public event {
public:
	Cd4Test(const double Time); //constructor
	~Cd4Test(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	//Some private stuff
	
};

/////////////////////
/////////////////////



#endif /* defined(__priorityQ__events__) */
