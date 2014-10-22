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

void SeedHiv(person * const thePerson)
{
	D(cout << "Seeding Hiv." << endl);
	
	/* HivIncidence function run every year from 1975 (theRng->doub() allows the exact time to vary within the year) */
//	double yr [55];
//	for(size_t i = 0; i < 55; i++) {
//		yr[i] = (5 + i + theRng->doub()) * 365.25;
//		new HivIncidence(thePerson,yr[i]);
//	}

		//For development purposes.
	new HivIncidence(thePerson,theQ->GetTime());
}

////////////////////
////////////////////

void UpdateEvents(person * const thePerson)
{
	//Need to take currentTime from somewhere, theQ?
	D(cout << "\tUpdateEvents executed." << endl);
	D(cout << "\tUpdateEvents time = " << theQ->GetTime() << endl);
	
	// Split tasks into multiple functions.
	
	/* Natural History Updates */
	UpdateAge(thePerson);
	
	/* Cascade Updates */
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
