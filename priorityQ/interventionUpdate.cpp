//
//  interventionUpdate.cpp
//  priorityQ
//
//  Created by Jack Olney on 03/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "interventionUpdate.h"
#include "interventionEvents.h"
#include "cascadeUpdate.h"
#include "cascadeEvents.h"
#include "rng.h"
#include "eventQ.h"
#include "toolbox.h"

extern eventQ * theQ;
extern Rng * theRng;

using namespace std;

////////////////////
////////////////////

void ScheduleHctHivTest(person * const thePerson, const bool poc)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 14610 && theQ->GetTime() < 21915) {
		const double diagDay = theRng->SampleExpDist(hctHivTestTime);
		if(diagDay <= 365.25)
			new HctHivTest(thePerson,theQ->GetTime() + diagDay,poc);
	}
}

////////////////////
////////////////////

void SchedulePerpetualHctHivTest(person * const thePerson)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 14610 && theQ->GetTime() < 21915)
		new HctHivTest(thePerson,theQ->GetTime() + (theRng->doub() * 365.25),0);
}

////////////////////
////////////////////

bool HctLinkage(person * const thePerson)
{
	if(thePerson->GetDiagnosisCount() > 1) {
		if(theRng->Sample(hctProbLinkPreviouslyDiagnosed))
			return true;
		else
			return false;
	} else {
		if(theRng->Sample(hctProbLink))
			return true;
		else
			return false;
	}
}

////////////////////
////////////////////

void ScheduleImmediateArt(person * const thePerson)
{
	new ArtInitiation(thePerson,theQ->GetTime());
}

////////////////////
////////////////////
