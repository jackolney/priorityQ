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
	double yr [55];
	for(size_t i = 0; i < 55; i++) {
//		yr[i] = (5 + i) * 365.25;
		yr[i] = (5 + i + theRng->doub()) * 365.25;
		if(thePerson->GetBirthDay() < yr[i])
			new HivIncidence(thePerson,yr[i]);
	}

		//For development purposes.
//	new HivIncidence(thePerson,theQ->GetTime());
}

////////////////////
////////////////////

void UpdateAge(person * const thePerson)
{
	thePerson->SetAge(theQ->GetTime());
}

////////////////////
////////////////////

void ScheduleCd4Update(person * const thePerson)
{
	D(cout << "ScheduleCd4Update called." << endl);

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
	
	if((!thePerson->GetArtInitiationState() || (thePerson->GetArtInitiationState() && !thePerson->GetArtAdherenceState())) && thePerson->GetCurrentCd4() > 1) {
		event * theEvent = new Cd4Decline(thePerson, theQ->GetTime() + theRng->SampleExpDist(Cd4DeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-2] * 365.25));
		D(cout << "\tCd4Decline from " << thePerson->GetCurrentCd4() << " to occur on = " << theEvent->GetTime() << endl);
	}
	else if(thePerson->GetArtInitiationState() && thePerson->GetArtAdherenceState() && thePerson->GetCurrentCd4() < 3) {
		event * theEvent = new Cd4Recover(thePerson, theQ->GetTime() + theRng->SampleExpDist(Cd4RecoverTimeArt [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
		D(cout << "\tCd4Recover from " << thePerson->GetCurrentCd4() << " to occur on = " << theEvent->GetTime() << endl);
	}

}

////////////////////
////////////////////

void ScheduleWhoUpdate(person * const thePerson)
{
	D(cout << "ScheduleWhoUpdate called." << endl);
	
		//WhoTime [WHO-1][CD4-1]
	const double WhoDeclineTime [3][4] =
	{
		{3.60827175,3.60838000,3.60838000,111.84994839},
		{4.50168495,4.50182000,4.50182000,139.54415407},
		{2.46547204,2.46554600,2.46554600,76.42520822}
	};
	
		//WhoTimeArt [WHO-1][CD4-1]
	const double WhoDeclineTimeArt [3][4] =
	{
		{3.85125925,3.85137479,3.85137479,119.38212479},
		{4.80483650,4.80498064,4.80498064,148.94130802},
		{2.63140956,2.63148850,2.63148850,81.56897372}
	};
	
		//WhoRecoverTimeArt [WHO from->to] = {2->1,3->2,4->3}
	const double WhoRecoverTimeArt [3] = {0.47176100,0.32243400,0.03783180};
	
	
	if((!thePerson->GetArtInitiationState() || (thePerson->GetArtInitiationState() && !thePerson->GetArtAdherenceState())) && thePerson->GetCurrentWho() < 4) {
		event * theEvent = new WhoDecline(thePerson, theQ->GetTime() + theRng->SampleExpDist(WhoDeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
		D(cout << "\tWhoDecline from " << thePerson->GetCurrentWho() << " to occur on = " << theEvent->GetTime() << endl);
	}
	else if(thePerson->GetArtInitiationState() && thePerson->GetArtAdherenceState()) {
		if(thePerson->GetCurrentWho() < 4) {
			event * theDeclineEvent = new WhoDecline(thePerson, theQ->GetTime() + theRng->SampleExpDist(WhoDeclineTimeArt [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
			D(cout << "\tWhoDecline (ART) from " << thePerson->GetCurrentWho() << " to occur on = " << theDeclineEvent->GetTime() << endl);
		}
		
		if(thePerson->GetCurrentWho() > 1) {
			event * theRecoverEvent = new WhoRecover(thePerson, theQ->GetTime() + theRng->SampleExpDist(WhoRecoverTimeArt [thePerson->GetCurrentWho()-2] * 365.25));
			D(cout << "\tWhoRecover (ART) from " << thePerson->GetCurrentWho() << " to occur on = " << theRecoverEvent->GetTime() << endl);
		}
	}
}

////////////////////
////////////////////
