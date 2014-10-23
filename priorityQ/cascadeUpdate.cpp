//
//  updateCascade.cpp
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "toolbox.h"
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



////////////////////
////////////////////

void UpdateTreatmentGuidelines(person * const thePerson, unsigned int theCd4, unsigned int theWho)
{
	thePerson->UpdateTxGuidelines(theCd4,theWho);
	D(cout << "TxGuidelines Updated (Cd4 = " << theCd4 << ", Who = " << theWho << ")." << endl);
}

////////////////////
////////////////////

void ScheduleHctHivTest(person * const thePerson)
{
		//To be filled in when including the interventions.
}

////////////////////
////////////////////

void ScheduleVctHivTest(person * const thePerson)
{
	if(theQ->GetTime() >= 12418) {
		D(cout << "Scheduling VctHivTest." << endl);
		new VctHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(vctHivTestTime));
	}
}

////////////////////
////////////////////

void SchedulePictHivTest(person * const thePerson)
{
	if(theQ->GetTime() >= 12418 && thePerson->GetSeroStatus()) {
		D(cout << "Scheduling PictHivTest." << endl);
		if(thePerson->GetCurrentWho() < 3) {
			if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4ResultState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_AsymptomaticNoCd4Result));
			else if(thePerson->GetEverCd4ResultState() && (thePerson->GetCurrentCd4() > thePerson->GetCd4TxGuideline() || thePerson->GetCurrentWho() < thePerson->GetWhoTxGuideline()))
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_AsymptomaticCd4ResultNotEligible));
			else if(thePerson->GetEverCd4ResultState() && (thePerson->GetCurrentCd4() <= thePerson->GetCd4TxGuideline() || thePerson->GetCurrentWho() >= thePerson->GetWhoTxGuideline()))
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_AsymptomaticCd4ResultEligible));
		} else {
			if(!thePerson->GetDiagnosedState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_SymptomaticOblivious));
			else if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4ResultState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_SymptomaticNoCd4Result));
			else if(thePerson->GetEverCd4ResultState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_SymptomaticCd4Result));
		}
	}
}

////////////////////
////////////////////

bool HctLinkage(person * const thePerson)
{
	if(thePerson->GetDiagnosisCount() > 1)
		return theRng->Sample(hctProbLinkPreviouslyDiagnosed);
	else
		return theRng->Sample(hctProbLink);
}

////////////////////
////////////////////

bool VctLinkage(person * const thePerson)
{
	return theRng->Sample(vctProbLink);
}

////////////////////
////////////////////

bool PictLinkage(person * const thePerson)
{
	return theRng->Sample(pictProbLink);
}

////////////////////
////////////////////

void ScheduleInitialCd4TestAfterHct(person * const thePerson)
{
	new Cd4Test(thePerson,theQ->GetTime() + theRng->SampleExpDist(hctCd4TestTime[thePerson->GetCurrentCd4()-1]));
}

////////////////////
////////////////////

void SchedulePreArtCd4Test(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() &&
	   thePerson->GetSeroStatus() &&
	   !thePerson->GetEverCd4TestState())
		new Cd4Test(thePerson,theQ->GetTime() + theRng->SampleExpDist(cd4TestTime));
}

////////////////////
////////////////////

void ScheduleArtInitiation(person * const thePerson)
{
	if(thePerson->GetDiagnosedState() &&
	   thePerson->GetSeroStatus() &&
	   thePerson->GetEverCd4TestState() &&
	   !thePerson->GetArtInitiationState())
		new ArtInitiation(thePerson,theQ->GetTime() + theRng->SampleExpDist(artInitiationTime));
}

////////////////////
////////////////////
