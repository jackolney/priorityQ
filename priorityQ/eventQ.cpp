//
//  eventQ.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "event.h"
#include "events.h"
#include "eventQ.h"
#include "rng.h"
#include "person.h"

extern Rng * theRng;
extern eventQ * theQ;
extern person * thePerson;


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
		UpdateQ(&currentTime); // UpdateQ will update iQ with relevant events (regardless of whether event ran, this is to ensure that events dependant on time are accounted for.)
		delete nextEvent;
	}
	return;
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

/* Define UpdateQ() */
//This function schedules the relevant events to occur based up on time / health etc.
void eventQ::UpdateQ(const double * theTime)
{
	cout << "Updating iQ." << endl;
	cout << "UpdateQ.Time is = " << *theTime << endl;
	
	if (*theTime == 10 && thePerson->GetGender()) {
		cout << "Hey, this is pretty neat. It only executes if time = 20 and you are Male." << endl;
		event * theEvent = new Cd4Test(25);
		theQ->AddEvent(theEvent);
		// Don't delete theEvent.
		}
	
	// Include functions here that farm out the code to other places. Makes it neater.
	
}