//
//  event.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "event.h"

/* Define constructor */
event::event(const double Time, void (*funcAddr)()) : eventTime(Time)
{
	funcPtr = funcAddr;
}

/* Define desctructor */
event::~event()
{}