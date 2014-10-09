//
//  event.h
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__event__
#define __priorityQ__event__

#include <stdio.h>

/* Define event class */
class event {
public:
	event(const double Time); //Constructor
	virtual ~event(); //Destructor
	
	/* Methods */
	virtual void Execute() = 0; //This is a PURE virtual function - as it is not defined in event.cpp but differently in derived classes.
	
	//		double time = 0; //define time - make private eventually.

	/*Accessor methods*/
	double GetTime() const {return eventTime;}
	// Include a "GetFun()" when private.
protected:
	const double eventTime = 0;
	
};

#endif /* defined(__priorityQ__event__) */