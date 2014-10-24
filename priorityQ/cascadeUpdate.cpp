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

void UpdateTreatmentGuidelines(person * const thePerson, unsigned int theCd4, unsigned int theWho)
{
	thePerson->UpdateTxGuidelines(theCd4,theWho);
	D(cout << "TxGuidelines Updated (Cd4 = " << theCd4 << ", Who = " << theWho << ")." << endl);
}

////////////////////
////////////////////

void ScheduleHctHivTest(person * const thePerson)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 14610) {
		for(size_t i = 0; i < 20; i++) {
			new HctHivTest(thePerson,theQ->GetTime() + (i * 365.25) + theRng->SampleExpDist(hctHivTestTime));
		}
	}
}

////////////////////
////////////////////

void ScheduleVctHivTest(person * const thePerson)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 12418) {
		D(cout << "Scheduling VctHivTest." << endl);
		new VctHivTest(thePerson,theQ->GetTime() + theRng->SampleExpDist(vctHivTestTime));
	}
}

////////////////////
////////////////////

void SchedulePictHivTest(person * const thePerson)
{
	if(thePerson->GetBirthDay() != 0 && theQ->GetTime() >= 12418 && thePerson->GetSeroStatus()) {
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
	if(thePerson->GetDiagnosisCount() > 1) {
		if(theRng->Sample(1)) { //hctProbLinkPreviouslyDiagnosed
			D(cout << "Linked to care after Hct (previously diagnosed)." << endl);
			return true;
		} else {
			D(cout << "Failed to link to care after Hct (previously diagnosed)." << endl);
			return false;
		}
	}
	else {
		if(theRng->Sample(1)) { //hctProbLink
			D(cout << "Linked to care after Hct." << endl);
			return true;
		} else {
			D(cout << "Failed to link to care after Hct." << endl);
			return false;
		}
	}
}

////////////////////
////////////////////

bool VctLinkage(person * const thePerson)
{
	if(theRng->Sample(1)) { //vctProbLink
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
	if(theRng->Sample(1)) { //pictProbLink
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
		 case 1: return theRng->Sample(1); break; //hctShortTermRetention
		 case 2: return theRng->Sample(1); break; //vctShortTermRetention
		 case 3: return theRng->Sample(1); break; //pictShortTermRetention
		 default: return false;
	 }
	}
	else
		switch(thePerson->GetDiagnosisRoute()) {
		 case 1: return theRng->Sample(1); break; //hctLongTermRetention
		 case 2: return theRng->Sample(1); break; //vctLongTermRetention
		 case 3: return theRng->Sample(1); break; //pictLongTermRetention
		 default: return false;
	 }
}

////////////////////
////////////////////

bool AttendCd4TestResult(person * const thePerson)
{
	if(theRng->Sample(1))
		return thePerson->Alive();
	else
		return false;
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
