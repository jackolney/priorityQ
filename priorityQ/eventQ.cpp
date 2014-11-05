//
//  eventQ.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "event.h"
#include "events.h"
#include "eventQ.h"
#include "rng.h"
#include "person.h"
#include "cohort.h"
#include "update.h"

extern Rng * theRng;
extern eventQ * theQ;

using namespace std;

/* Define operator for timeComparison */
bool timeComparison::operator()(const event *lhs, const event *rhs) const
{
	return lhs->GetTime() > rhs->GetTime();
}

/* Define constructor */
eventQ::eventQ(const double startTime) :
currentTime(startTime),
incrementalTime(0)
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
	while(!Empty()) {
		event * nextEvent = GetTop();
		UpdateTime(nextEvent->GetTime());
		PopTop();
		if(nextEvent->CheckValid())
			nextEvent->Execute();
		else
			nextEvent->Cancel();
		delete nextEvent;
		D(cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tcurrentTime is = " << currentTime << " (year = " << currentTime / 365.25 << ")" <<  endl);
		D(cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\ttheQ size is = " << theQ->Size() << endl);
	}
	return;
}

/* Define Empty() */
bool eventQ::Empty() const
{
	return iQ.empty();
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
size_t eventQ::Size() const
{
	return iQ.size();
}

/* Define UpdateTime() */
void eventQ::UpdateTime(const double theTime)
{
	incrementalTime = theTime - currentTime;
	currentTime = theTime;
}