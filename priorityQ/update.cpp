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

void ScheduleCd4Update(person * const thePerson)
{
	cout << "ScheduleCd4Update called." << endl;

		//Cd4Time [WHO-1] [CD4-2 (4,3,2)]
	double Cd4Time [4] [3] =
	{
		{2.79458000,2.69187000,7.98158000},
		{2.79458000,2.69187000,7.98158000},
		{1.97615529,1.90352509,5.64408302},
		{0.83767622,0.80688886,2.39248106}
	};
	
		//Cd4TimeArt [WHO-1] [CD4-1 (1,2)]
	double Cd4TimeArt [4] [2] =
	{
		{0.17366500,0.44638000},
		{0.17366500,0.44638000},
		{0.27560405,0.70839913},
		{1.41480920,3.63655620}
	};
	
	if(!thePerson->GetArtInitiationState() && thePerson->GetCurrentCd4() > 1) {
		event * theEvent = new Cd4Decline(thePerson, theQ->GetTime() + (Cd4Time [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-2] * 365.25));
		cout << "\tCd4Decline from " << thePerson->GetCurrentCd4() << " to occur on = " << theEvent->GetTime() << endl;
	}
	else if(thePerson->GetArtInitiationState() && thePerson->GetCurrentCd4() < 3) {
		event * theEvent = new Cd4Recover(thePerson, theQ->GetTime() + (Cd4TimeArt [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
		cout << "\tCd4Recover from " << thePerson->GetCurrentCd4() << " to occur on = " << theEvent->GetTime() << endl;
	}

}

////////////////////
////////////////////

void ScheduleWhoUpdate(person * const thePerson)
{
	cout << "ScheduleWhoUpdate called." << endl;
}

////////////////////
////////////////////