//
//  cascadeEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "cascadeEvents.h"
#include "cascadeUpdate.h"
#include "event.h"
#include "person.h"
#include "update.h"
#include "cohort.h"

using namespace std;

/////////////////////
/////////////////////

SeedInitialHivTests::SeedInitialHivTests(person * const thePerson) :
event(12418),
pPerson(thePerson)
{
	D(cout << "InitialHivTests scheduled to begin in " <<  this->GetTime() << "." << endl);
};

SeedInitialHivTests::~SeedInitialHivTests()
{}

bool SeedInitialHivTests::CheckValid()
{
	return pPerson->Alive();
}

void SeedInitialHivTests::Execute()
{
	UpdateTreatmentGuidelines(pPerson,1,4);
	ScheduleVctHivTest(pPerson);
	SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

SeedTreatmentGuidelinesUpdate::SeedTreatmentGuidelinesUpdate(person * const thePerson) :
event(14975),
pPerson(thePerson)
{
	D(cout << "Treatment guidelines will update on 14975" << endl);
}

SeedTreatmentGuidelinesUpdate::~SeedTreatmentGuidelinesUpdate()
{}

bool SeedTreatmentGuidelinesUpdate::CheckValid()
{
	return pPerson->Alive();
}

void SeedTreatmentGuidelinesUpdate::Execute()
{
	UpdateTreatmentGuidelines(pPerson,2,3);
}

/////////////////////
/////////////////////

HctHivTest::HctHivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetHctHivTestDate(Time);
	D(cout << "HctHivTest scheduled for day = " << Time << endl);	
}

HctHivTest::~HctHivTest()
{}

bool HctHivTest::CheckValid()
{
	if(pPerson->GetHctHivTestDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void HctHivTest::Execute()
{
	D(cout << "HctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,1);
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(HctLinkage(pPerson))
			ScheduleInitialCd4TestAfterHct(pPerson);
	}
	UpdateEvents(pPerson);
}

/////////////////////
/////////////////////

VctHivTest::VctHivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetVctHivTestDate(Time);
	D(cout << "VctHivTest scheduled for day = " << Time << endl);
}

VctHivTest::~VctHivTest()
{}

bool VctHivTest::CheckValid()
{
	if(pPerson->GetVctHivTestDate() == GetTime())
		return pPerson->Alive();
	else {
		ScheduleVctHivTest(pPerson);
		return false;
	}
}

void VctHivTest::Execute()
{
	D(cout << "VctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,2);
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(VctLinkage(pPerson))
			new Cd4Test(pPerson,GetTime()); //Schedules a CD4 test immediately.
	}
	UpdateEvents(pPerson);
	ScheduleVctHivTest(pPerson);
};

/////////////////////
/////////////////////

PictHivTest::PictHivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetPictHivTestDate(Time);
	D(cout << "PictHivTest scheduled for day = " << Time << endl);
}

PictHivTest::~PictHivTest()
{}

bool PictHivTest::CheckValid()
{
	if(pPerson->GetPictHivTestDate() == GetTime())
		return pPerson->Alive();
	else {
		SchedulePictHivTest(pPerson);
		return false;
	}
}

void PictHivTest::Execute()
{
	D(cout << "PictHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,3);
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(PictLinkage(pPerson))
			new Cd4Test(pPerson,GetTime()); //Schedules a CD4 test immediately.
	}
	UpdateEvents(pPerson);
	SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

Cd4Test::Cd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Cd4Test scheduled for day = " << Time << endl);
}

Cd4Test::~Cd4Test()
{}

bool Cd4Test::CheckValid()
{
	return true;
}

void Cd4Test::Execute()
{
	D(cout << "Entered care." << endl);
	D(cout << "Cd4Test executed." << endl);
	pPerson->SetInCareState(true);
	pPerson->SetEverCd4TestState(true);
	if(ReceiveCd4TestResult(pPerson))
		ScheduleCd4TestResult(pPerson);
	UpdateEvents(pPerson);
};

/////////////////////
/////////////////////

Cd4TestResult::Cd4TestResult(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Cd4TestResult scheduled for day = " << Time << endl);
}

Cd4TestResult::~Cd4TestResult()
{}

bool Cd4TestResult::CheckValid()
{
	return AttendCd4TestResult(pPerson);
}

void Cd4TestResult::Execute()
{
	D(cout << "Cd4TestResult executed." << endl);
	pPerson->SetEverCD4TestResultState(true);
	if(pPerson->GetEligible())
		ScheduleArtInitiation(pPerson);
	else
		SchedulePreArtCd4Test(pPerson);
	UpdateEvents(pPerson);
}

/////////////////////
/////////////////////

ArtInitiation::ArtInitiation(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Eligible for ART." << endl);
	D(cout << "ArtInitiation scheduled for day = " << Time << endl);
}

ArtInitiation::~ArtInitiation()
{}

bool ArtInitiation::CheckValid()
{
	return true;
}

void ArtInitiation::Execute()
{
	D(cout << "ArtInitiation executed." << endl);
	pPerson->SetArtInitiationState(true);
	ScheduleCd4Update(pPerson);
	ScheduleWhoUpdate(pPerson);
	UpdateEvents(pPerson);
}

/////////////////////
/////////////////////
