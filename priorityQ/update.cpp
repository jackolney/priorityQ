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

////////////////////
////////////////////

void SeedEvents(person * const thePerson, const double Time)
{
	cout << "Seeding initial events." << endl;
	
	if (thePerson->GetBirthDay() == Time) { //check to ensure that events get seeded on BirthDay.
		event * theEvent = new HivTest(thePerson,Time + theRng->SampleExpDist(25));
		theQ->AddEvent(theEvent);
		cout << "HivTest scheduled for day = " << theEvent->GetTime() << endl;
		}
	
}

////////////////////
////////////////////

void UpdateEvents(person * const thePerson)
{
	//Need to take currentTime from somewhere, theQ?
	cout << "UpdateEvents executed." << endl;
	cout << "UpdateEvents time = " << theQ->GetTime() << endl;
	
	// Split tasks into multiple functions.
	
	UpdateAge(thePerson);
	
	ScheduleCd4Test(thePerson);
	
}

////////////////////
////////////////////

void UpdateAge(person * const thePerson)
{
	thePerson->SetAge(theQ->GetTime());
	cout << "Updated Age = " << thePerson->GetAge() << endl;
}

////////////////////
////////////////////

void ScheduleCd4Test(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() && !thePerson->GetCd4TestState()) {
		event * theEvent = new Cd4Test(thePerson,theQ->GetTime() + theRng->SampleExpDist(25));
		theQ->AddEvent(theEvent);
		cout << "Cd4Test scheduled for day = " << theEvent->GetTime() << endl;		
	}
}