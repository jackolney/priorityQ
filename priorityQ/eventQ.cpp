//
//  eventQ.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "event.h"
#include "eventQ.h"

using namespace std;

/* Define operator for timeComparison */
bool timeComparison::operator()(const event *lhs, const event *rhs) const
{
	return lhs->GetTime() > rhs->GetTime();
}

/* Define constructor */
eventQ::eventQ(const double startTime,const double stopTime) : currentTime(startTime), endTime(stopTime)
{}

/* Define destructor */
eventQ::~eventQ()
{}

/* Define AddEvent() */
void eventQ::AddEvent(event * const theEvent)
{
	iQ.push(theEvent);
}

/* Define RunEvents() */
void eventQ::RunEvents()
{
	while(!Empty() && currentTime < endTime) {
		event * nextEvent = GetTop();
		currentTime = nextEvent->GetTime();
		cout << "Current time is = " << currentTime << endl;
		PopTop();
//		if(!nextEvent->Cancelled()) // Checks to see if event is cancelled, if so doesn't even bother doing anything else should just PopTop() it.
			nextEvent->Execute();
		UpdateQ(); // UpdateQ will update iQ with relevant events (regardless of whether event ran, this is to ensure that events dependant on time are accounted for.)
		delete nextEvent;
	}
	return;
}

/* Define UpdateQ */
void eventQ::UpdateQ()
{
	cout << "Updating iQ." << endl;
}


/* Define Empty() */
bool eventQ::Empty() const
{
	return iQ.empty(); //Returns 1 if iQ is empty.
}

/* Define GetTop() */
event * eventQ::GetTop()
{
	event * theEvent = iQ.top();
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