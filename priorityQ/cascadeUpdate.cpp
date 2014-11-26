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
#include "interventionEvents.h"
#include "rng.h"
#include "eventQ.h"

extern Rng * theRng;
extern eventQ * theQ;

using namespace std;

////////////////////
////////////////////

void UpdateTreatmentGuidelines(person * const thePerson, unsigned int theCd4, unsigned int theWho)
{
	thePerson->UpdateTxGuidelines(theCd4,theWho);
	D(cout << "TxGuidelines Updated (Cd4 = " << theCd4 << ", Who = " << theWho << ")." << endl);
}

////////////////////
////////////////////

void ScheduleVctHivTest(person * const thePerson)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 12418) {
		D(cout << "Scheduling VctHivTest." << endl);
		new VctHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(vctHivTestTime),vctPocFlag);
	}
}

////////////////////
////////////////////

void SchedulePictHivTest(person * const thePerson)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 12418 && thePerson->GetSeroStatus()) {
		D(cout << "Scheduling PictHivTest." << endl);
		if(thePerson->GetCurrentWho() < 3) {
			if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4TestResultState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_AsymptomaticNoCd4Result));
			else if(thePerson->GetEverCd4TestResultState() && (thePerson->GetCurrentCd4() > thePerson->GetCd4TxGuideline() || thePerson->GetCurrentWho() < thePerson->GetWhoTxGuideline()))
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_AsymptomaticCd4ResultNotEligible));
			else if(thePerson->GetEverCd4TestResultState() && (thePerson->GetCurrentCd4() <= thePerson->GetCd4TxGuideline() || thePerson->GetCurrentWho() >= thePerson->GetWhoTxGuideline()))
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_AsymptomaticCd4ResultEligible));
		} else {
			if(!thePerson->GetDiagnosedState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_SymptomaticOblivious));
			else if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4TestResultState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_SymptomaticNoCd4Result));
			else if(thePerson->GetEverCd4TestResultState())
				new PictHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(pictHivTestTime_SymptomaticCd4Result));
		}
	}
}

////////////////////
////////////////////

bool VctLinkage(person * const thePerson)
{
	if(theRng->Sample(vctProbLink)) {
		D(cout << "Linked to care after Vct." << endl);
		return true;
	} else {
		D(cout << "Failed to link to care after Vct." << endl);
		return false;
	}
}

////////////////////
////////////////////

bool PictLinkage(person * const thePerson)
{
	if(theRng->Sample(pictProbLink)) {
		D(cout << "Linked to care after Pict." << endl);
		return true;
	} else {
		D(cout << "Failed to link to care after Pict." << endl);
		return false;
	}
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
	new Cd4Test(thePerson,theQ->GetTime() + theRng->SampleExpDist(cd4TestTime));
}

////////////////////
////////////////////

void ScheduleCd4TestResult(person * const thePerson)
{
	new Cd4TestResult(thePerson,theQ->GetTime() + theRng->SampleExpDist(cd4ResultTime));
}

////////////////////
////////////////////

bool ReceiveCd4TestResult(person * const thePerson)
{
	if(thePerson->GetCd4TestCount() <= 1) {
	 switch(thePerson->GetDiagnosisRoute()) {
		 case 1: return theRng->Sample(hctShortTermRetention);  break;
		 case 2: return theRng->Sample(vctShortTermRetention);  break;
		 case 3: return theRng->Sample(pictShortTermRetention); break;
		 default: thePerson->SetInCareState(false); return false;
	 }
	}
	else
		switch(thePerson->GetDiagnosisRoute()) {
		 case 1: return theRng->Sample(hctLongTermRetention);  break;
		 case 2: return theRng->Sample(vctLongTermRetention);  break;
		 case 3: return theRng->Sample(pictLongTermRetention); break;
		 default: thePerson->SetInCareState(false); return false;
	 }
}

////////////////////
////////////////////

bool AttendCd4TestResult(person * const thePerson)
{
	if(theRng->Sample(cd4ResultProbAttend) && !thePerson->GetEverArt())
		return thePerson->Alive();
	else {
		thePerson->SetInCareState(false);
		return false;
	}
}

////////////////////
////////////////////

bool SecondaryCd4Test(person * const thePerson)
{
	switch(thePerson->GetDiagnosisRoute()) {
		case 1: return theRng->Sample(hctProbSecondaryCd4Test); break;
		case 2: return theRng->Sample(vctProbSecondaryCd4Test); break;
		case 3: return theRng->Sample(pictProbSecondaryCd4Test); break;
		default: thePerson->SetInCareState(false); return false;
	}
	
}

////////////////////
////////////////////

void FastTrackArt(person * const thePerson)
{
	if(!thePerson->GetEverCd4TestResultState() && thePerson->GetCd4TestCount() == 1 && thePerson->GetDiagnosisRoute() > 1)
		new ArtInitiation(thePerson,theQ->GetTime());
}

////////////////////
////////////////////

void ScheduleArtInitiation(person * const thePerson)
{
	new ArtInitiation(thePerson,theQ->GetTime() + theRng->SampleExpDist(artInitiationTime));
}

////////////////////
////////////////////

void ScheduleArtDropout(person * const thePerson)
{
	const double artDropoutDate = theRng->SampleExpDist(artDropoutTimeOneYear);
	
	if(artDropoutDate < 365.25)
		new ArtDropout(thePerson,theQ->GetTime() + artDropoutDate);
	else
		new ArtDropout(thePerson,theQ->GetTime() + 365.25 + theRng->SampleExpDist(artDropoutTimeTwoYear));
	
}

////////////////////
////////////////////
