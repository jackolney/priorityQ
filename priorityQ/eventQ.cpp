//
//  eventQ.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "event.h"
#include "eventQ.h"

/* Define operator for timeComparison */
bool timeComparison::operator()(const event *lhs, const event *rhs) const
{
	return lhs->GetTime() > rhs->GetTime();
}

/* Define constructor */
eventQ::eventQ() : currentTime(0)
{}

/* Define destructor */
eventQ::~eventQ()
{}

/* Define AddEvent() */
void eventQ::AddEvent(event * const theEvent)
{
	iQ.push(theEvent);
}

/* Define GetTop() */
event * eventQ::GetTop()
{
	event * theEvent = iQ.top();
	//	iQ.pop(); // Could be useful eventually?
	return theEvent;
}

/* Define PopTop() */
void eventQ::PopTop()
{
	iQ.pop();
}

/* Define Size() */
size_t eventQ::Size() const //const after a function declaration means the function is not allowed to change any class members.
{
	return iQ.size();
}