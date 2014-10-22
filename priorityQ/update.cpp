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
	const double Cd4DeclineTime [4] [3] =
	{
		{2.79458000,2.69187000,7.98158000},
		{2.79458000,2.69187000,7.98158000},
		{1.97615529,1.90352509,5.64408302},
		{0.83767622,0.80688886,2.39248106}
	};
	
		//Cd4TimeArt [WHO-1] [CD4-1 (1,2)]
	const double Cd4RecoverTimeArt [4] [2] =
	{
		{0.17366500,0.44638000},
		{0.17366500,0.44638000},
		{0.27560405,0.70839913},
		{1.41480920,3.63655620}
	};
	
	if(!thePerson->GetArtInitiationState() && thePerson->GetCurrentCd4() > 1) {
		event * theEvent = new Cd4Decline(thePerson, theQ->GetTime() + (Cd4DeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-2] * 365.25));
		thePerson->SetCd4DeclineDate(theEvent->GetTime());
		cout << "\tCd4Decline from " << thePerson->GetCurrentCd4() << " to occur on = " << theEvent->GetTime() << endl;
	}
	else if(thePerson->GetArtInitiationState() && thePerson->GetCurrentCd4() < 3) {
		event * theEvent = new Cd4Recover(thePerson, theQ->GetTime() + (Cd4RecoverTimeArt [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
		thePerson->SetCd4RecoverDate(theEvent->GetTime());
		cout << "\tCd4Recover from " << thePerson->GetCurrentCd4() << " to occur on = " << theEvent->GetTime() << endl;
	}

}

////////////////////
////////////////////

void ScheduleWhoUpdate(person * const thePerson)
{
	cout << "ScheduleWhoUpdate called." << endl;
	
		//WhoTime [WHO-1][CD4-1]
	const double WhoDeclineTime [3][4] =
	{
	/* <200 / 200350 / 350500 / 500 */
	/*WHO 1->2*/	{3.60827175,3.60838000,3.60838000,111.84994839},
	/*WHO 2->3*/	{4.50168495,4.50182000,4.50182000,139.54415407},
	/*WHO 3->4*/	{2.46547204,2.46554600,2.46554600,76.42520822}
	};
		//Condition is currentWho < 4
//	cout << WhoDeclineTime[1-1][1-1] << endl;

	cout << thePerson->GetCurrentWho() << " = currentWho" << endl;
	cout << thePerson->GetCurrentCd4() << " = currentCd4" << endl;
//	event * theEvent = new WhoDecline(thePerson, theQ->GetTime() + (WhoDeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
	
	if(!thePerson->GetArtInitiationState() && thePerson->GetCurrentWho() < 4) {
		event * theEvent = new WhoDecline(thePerson, theQ->GetTime() + (WhoDeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
		thePerson->SetWhoDeclineDate(theEvent->GetTime());
		cout << "\tWhoDecline from " << thePerson->GetCurrentWho() << " to occur on = " << theEvent->GetTime() << endl;
	}
//	else if(thePerson->GetArtInitiationState())
	
	
	
		//WhoTimeArt [WHO-1][CD4-1]
	const double WhoDeclineTimeArt [3][4] =
	{
	/* <200 / 200350 / 350500 / 500 */
	/*WHO 1->2*/	{3.85125925,3.85137479,3.85137479,119.38212479},
	/*WHO 2->3*/	{4.80483650,4.80498064,4.80498064,148.94130802},
	/*WHO 3->4*/	{2.63140956,2.63148850,2.63148850,81.56897372}
	};
		//Condition is currentWho < 4
//	cout << WhoDeclineTimeArt[1-1][1-1] << endl;
	
	
		//WhoRecoverTimeArt [WHO from->to] = {2->1,3->2,4->3}
	const double WhoRecoverTimeArt [3] = {0.47176100,0.32243400,0.03783180};
	
		//condition is currentWho > 1
//	cout << WhoRecoverTimeArt[1-2] << endl;

}

////////////////////
////////////////////