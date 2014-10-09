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

	/*Accessor methods*/
	double GetTime() const {return eventTime;}

	/* Can include cancelling methods here */
	
	
protected:
	const double eventTime = 0;
	
};

#endif /* defined(__priorityQ__event__) */