//
//  updateCascade.cpp
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "cascadeUpdate.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "cascadeEvents.h"
#include "rng.h"
#include "eventQ.h"

extern Rng * theRng;
extern eventQ * theQ;

using namespace std;

////////////////////
////////////////////

	//Expand to schedule Vct and a separate function for scheduling Pict and another for Hct.

void SeedEvents(person * const thePerson, const double Time)
{
	D(cout << "Seeding initial events." << endl);
	
	if (thePerson->GetBirthDay() == Time) { //check to ensure that events get seeded on BirthDay.
		event * theEvent = new VctHivTest(thePerson,Time + theRng->SampleExpDist(5.8 * 365.25));
		D(cout << "VctHivTest scheduled for day = " << theEvent->GetTime() << endl);
	}
	
	//Seed initial PICT test event too.
	
}

////////////////////
////////////////////

void ScheduleCd4Test(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() &&
	   thePerson->GetSeroStatus() &&
	   !thePerson->GetCd4TestState()) {
		event * theEvent = new Cd4Test(thePerson,theQ->GetTime() + theRng->SampleExpDist(25));
		D(cout << "Cd4Test scheduled for day = " << theEvent->GetTime() << endl);
	}
}

////////////////////
////////////////////

void ScheduleArtInitiation(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() &&
	   thePerson->GetSeroStatus() &&
	   thePerson->GetCd4TestState() &&
	   !thePerson->GetArtInitiationState()) {
		event * theEvent = new ArtInitiation(thePerson,theQ->GetTime() + theRng->SampleExpDist(25));
		D(cout << "ArtInitiation scheduled for day = " << theEvent->GetTime() << endl);
	}
}

////////////////////
////////////////////
