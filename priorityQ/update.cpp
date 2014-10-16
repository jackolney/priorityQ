//
//  update.cpp
//  priorityQ
//
//  Created by Jack Olney on 16/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "update.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "rng.h"
#include "eventQ.h"

extern Rng * theRng;
extern eventQ * theQ;

using namespace std;

void SeedEvents(person * const thePerson, const double Time) {

	cout << "Seeding events." << endl;
	// Need to tie an event occurring in time to a specific person.
	
	if (Time == 0) {
		event * theEvent = new HivTest(thePerson,theRng->SampleExpDist(25));
		theQ->AddEvent(theEvent);
		cout << "HivTest scheduled for day = " << theEvent->GetTime() << endl;
		}
	
}

void UpdateEvents(person * const thePerson) {
	//Need to take currentTime from somewhere, theQ?
	cout << "UpdateEvents executed." << endl;
	cout << "UpdateEvents time = " << theQ->GetTime() << endl;
}