//
//  update.cpp
//  priorityQ
//
//  Created by Jack Olney on 16/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
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
	D(cout << "Seeding initial events." << endl);
	
	if (thePerson->GetBirthDay() == Time) { //check to ensure that events get seeded on BirthDay.
		event * theEvent = new HivTest(thePerson,Time + theRng->SampleExpDist(25));
		D(cout << "HivTest scheduled for day = " << theEvent->GetTime() << endl);
		}
	
}

////////////////////
////////////////////

void UpdateEvents(person * const thePerson)
{
	//Need to take currentTime from somewhere, theQ?
	D(cout << "\tUpdateEvents executed." << endl);
	D(cout << "\tUpdateEvents time = " << theQ->GetTime() << endl);
	
	// Split tasks into multiple functions.
	
	UpdateAge(thePerson);
	
	ScheduleCd4Test(thePerson);
	
	ScheduleArtInitiation(thePerson);
	
}

////////////////////
////////////////////

void UpdateAge(person * const thePerson)
{
	thePerson->SetAge(theQ->GetTime());
	D(cout << "\tUpdated Age = " << thePerson->GetAge() << endl);
}

////////////////////
////////////////////

void ScheduleCd4Test(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() && !thePerson->GetCd4TestState()) {
		event * theEvent = new Cd4Test(thePerson,theQ->GetTime() + theRng->SampleExpDist(25));
		D(cout << "Cd4Test scheduled for day = " << theEvent->GetTime() << endl);
	}
}

////////////////////
////////////////////

void ScheduleArtInitiation(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() &&
	   thePerson->GetCd4TestState() &&
	   !thePerson->GetArtInitiationState()) {
		event * theEvent = new ArtInitiation(thePerson,theQ->GetTime() + theRng->SampleExpDist(25));
		D(cout << "ArtInitiation scheduled for day = " << theEvent->GetTime() << endl);
	}
}

////////////////////
////////////////////