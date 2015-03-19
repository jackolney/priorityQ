//
//  cascadeEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "toolbox.h"
#include "cascadeEvents.h"
#include "cascadeUpdate.h"
#include "event.h"
#include "person.h"
#include "update.h"
#include "cohort.h"
#include "impact.h"
#include "cost.h"
#include "interventionEvents.h"
#include "interventionUpdate.h"

using namespace std;

/////////////////////
/////////////////////

SeedInitialHivTests::SeedInitialHivTests(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "InitialHivTests scheduled to begin in " <<  this->GetTime() << "." << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
};

SeedInitialHivTests::~SeedInitialHivTests()
{}

bool SeedInitialHivTests::CheckValid()
{
	return pPerson->Alive();
}

void SeedInitialHivTests::Execute()
{
	if(!immediateArtFlag)
		UpdateTreatmentGuidelines(pPerson,1,4);
	ScheduleVctHivTest(pPerson,GetTime());
	SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

SeedTreatmentGuidelinesUpdate::SeedTreatmentGuidelinesUpdate(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Treatment guidelines will update on " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

SeedTreatmentGuidelinesUpdate::~SeedTreatmentGuidelinesUpdate()
{}

bool SeedTreatmentGuidelinesUpdate::CheckValid()
{
	if(!immediateArtFlag)
		return pPerson->Alive();
	else
		return false;
}

void SeedTreatmentGuidelinesUpdate::Execute()
{
	UpdateTreatmentGuidelines(pPerson,2,3);
}

/////////////////////
/////////////////////

VctHivTest::VctHivTest(person * const thePerson, const double Time, const bool poc) :
event(Time),
pPerson(thePerson),
pointOfCare(poc)
{
	thePerson->SetVctHivTestDate(Time);
	D(cout << "VctHivTest scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

VctHivTest::~VctHivTest()
{}

bool VctHivTest::CheckValid()
{
	if(pPerson->GetVctHivTestDate() == GetTime() && !pPerson->GetEverArt())
		return pPerson->Alive();
	else {
		return false;
	}
}

void VctHivTest::Execute()
{
	UpdateDaly(pPerson,GetTime());
	ChargeVctPictHivTest(pPerson);
	D(cout << "VctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,2,GetTime());
		D(cout << "Diagnosed as HIV-positive." << endl);
		SchedulePictHivTest(pPerson,GetTime());
		if(pointOfCare)
			new VctPocCd4Test(pPerson,GetTime());
		else if(VctLinkage(pPerson))
			new Cd4Test(pPerson,GetTime());
		else
			ChargePreArtClinicVisit(pPerson);
	}
	ScheduleVctHivTest(pPerson,GetTime());
};

/////////////////////
/////////////////////

PictHivTest::PictHivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetPictHivTestDate(Time);
	D(cout << "PictHivTest scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

PictHivTest::~PictHivTest()
{}

bool PictHivTest::CheckValid()
{
	if(pPerson->GetPictHivTestDate() == GetTime() && !pPerson->GetEverArt())
		return pPerson->Alive();
	else {
		return false;
	}
}

void PictHivTest::Execute()
{
	UpdateDaly(pPerson,GetTime());
	ChargeVctPictHivTest(pPerson);
	D(cout << "PictHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,3,GetTime());
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(PictLinkage(pPerson))
			new Cd4Test(pPerson,GetTime());
		else
			ChargePreArtClinicVisit(pPerson);
	}
	SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

Cd4Test::Cd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Cd4Test scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Cd4Test::~Cd4Test()
{}

bool Cd4Test::CheckValid()
{
	if(!pPerson->GetEverArt() && pPerson->Alive()) {
		if(!pocFlag)
			return true;
		else {
			new PocCd4Test(pPerson,GetTime());
			return false;
		}
	} else
		return false;
}

void Cd4Test::Execute()
{
	UpdateDaly(pPerson,GetTime());
	ChargePreArtClinicVisit(pPerson);
	ChargePreArtClinicCd4Test(pPerson);
	D(cout << "Entered care." << endl);
	D(cout << "Cd4Test executed." << endl);
	pPerson->SetEverCd4TestState(true);
	FastTrackArt(pPerson,GetTime());
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson,GetTime());
	else if(ReceiveCd4TestResult(pPerson,GetTime())) {
		ScheduleCd4TestResult(pPerson,GetTime());
		pPerson->SetInCareState(true,GetTime());
	}
};

/////////////////////
/////////////////////

Cd4TestResult::Cd4TestResult(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Cd4TestResult scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Cd4TestResult::~Cd4TestResult()
{}

bool Cd4TestResult::CheckValid()
{
	return AttendCd4TestResult(pPerson,GetTime());
}

void Cd4TestResult::Execute()
{
	UpdateDaly(pPerson,GetTime());
	ChargePreArtClinicCd4ResultVisit(pPerson);
	D(cout << "Cd4TestResult executed." << endl);
	pPerson->SetEverCd4TestResultState(true);
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson,GetTime());
	else if(pPerson->GetEligible()) {
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson,GetTime());
	} else {
		D(cout << "Not eligible for ART." << endl);
		if(SecondaryCd4Test(pPerson,GetTime()))
			SchedulePreArtCd4Test(pPerson,GetTime());
	}
	SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

ArtInitiation::ArtInitiation(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "ArtInitiation scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

ArtInitiation::~ArtInitiation()
{}

bool ArtInitiation::CheckValid()
{
	if(!pPerson->GetArtInitiationState() && !pPerson->GetEverArt())
		return pPerson->Alive();
	else
		return false;
}

void ArtInitiation::Execute()
{
	UpdateDaly(pPerson,GetTime());
	D(cout << "ArtInitiation executed." << endl);
	if(!pPerson->GetArtAdherenceState())
		D(cout << "NON-ADHERER to Art." << endl);
	pPerson->SetArtInitiationState(true,GetTime());
	ScheduleCd4Update(pPerson,GetTime());
	ScheduleWhoUpdate(pPerson,GetTime());
	ScheduleArtDropout(pPerson,GetTime());
	pPerson->UpdateInfectiousnessArray();
}

/////////////////////
/////////////////////

ArtDropout::ArtDropout(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "ArtDropout scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }	
}

ArtDropout::~ArtDropout()
{}

bool ArtDropout::CheckValid()
{
	return pPerson->Alive();
}

void ArtDropout::Execute()
{
	UpdateDaly(pPerson,GetTime());
	D(cout << "ArtDropout executed." << endl);
	pPerson->SetArtInitiationState(false,GetTime());
	ScheduleCd4Update(pPerson,GetTime());
	ScheduleWhoUpdate(pPerson,GetTime());
	pPerson->UpdateInfectiousnessArray();
}

/////////////////////
/////////////////////
