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
#include "rng.h"
#include "eventQ.h"
#include "toolbox.h"

extern eventQ * theQ;
extern Rng * theRng;

using namespace std;

/////////////////////
/////////////////////

SeedHct::SeedHct(person * const thePerson, const double Time, const bool poc) :
event(Time),
pPerson(thePerson),
pointOfCare(poc)
{
	D(cout << "Hct seeded for deployment on day = " << Time << endl);
}

SeedHct::~SeedHct()
{}

bool SeedHct::CheckValid()
{
	if(!pPerson->GetEverArt())
		return pPerson->Alive();
	else
		return false;
}

void SeedHct::Execute()
{
	ScheduleHctHivTest(pPerson,pointOfCare);
}

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

bool HctLinkage(person * const thePerson)
{
	if(thePerson->GetDiagnosisCount() > 1) {
		if(theRng->Sample(hctProbLinkPreviouslyDiagnosed)) {
			D(cout << "Linked to care after Hct (previously diagnosed)." << endl);
			return true;
		} else {
			D(cout << "Failed to link to care after Hct (previously diagnosed)." << endl);
			return false;
		}
	}
	else {
		if(theRng->Sample(hctProbLink)) {
			D(cout << "Linked to care after Hct." << endl);
			return true;
		} else {
			D(cout << "Failed to link to care after Hct." << endl);
			return false;
		}
	}
}