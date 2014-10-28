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
#include "impact.h"
#include "cost.h"

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
	if(pPerson->GetHctHivTestDate() == GetTime() && !pPerson->GetEverArt())
		return pPerson->Alive();
	else
		return false;
}

void HctHivTest::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	ChargeHctVisit(pPerson);
	D(cout << "HctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,1);
		D(cout << "Diagnosed as HIV-positive." << endl);
		SchedulePictHivTest(pPerson);
		if(HctLinkage(pPerson))
			ScheduleInitialCd4TestAfterHct(pPerson);
	}
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
	cout << boolalpha << pPerson->GetEverArt() << " = EVER ART." << endl;
	cout << boolalpha << pPerson->GetArtInitiationState() << " = ART INITIATION STATE." << endl;
	if(pPerson->GetVctHivTestDate() == GetTime() && !pPerson->GetEverArt())
		return pPerson->Alive();
	else {
		return false;
	}
}

void VctHivTest::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	ChargeVctPictHivTest(pPerson);
	D(cout << "VctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,2);
		D(cout << "Diagnosed as HIV-positive." << endl);
		SchedulePictHivTest(pPerson);
		if(VctLinkage(pPerson))
			new Cd4Test(pPerson,GetTime()); //Schedules a CD4 test immediately.
		else
			ChargePreArtClinicVisit(pPerson);
	}
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
	cout << boolalpha << pPerson->GetEverArt() << " = EVER ART." << endl;
	cout << boolalpha << pPerson->GetArtInitiationState() << " = ART INITIATION STATE." << endl;
	if(pPerson->GetPictHivTestDate() == GetTime() && !pPerson->GetEverArt())
		return pPerson->Alive();
	else {
		return false;
	}
}

void PictHivTest::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	ChargeVctPictHivTest(pPerson);
	D(cout << "PictHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,3);
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(PictLinkage(pPerson))
			new Cd4Test(pPerson,GetTime()); //Schedules a CD4 test immediately.
		else
			ChargePreArtClinicVisit(pPerson);
	}
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
	if(!pPerson->GetEverArt())
		return pPerson->Alive();
	else
		return false;
}

void Cd4Test::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	ChargePreArtClinicVisit(pPerson);
	ChargePreArtClinicCd4Test(pPerson);
	D(cout << "Entered care." << endl);
	D(cout << "Cd4Test executed." << endl);
	pPerson->SetInCareState(true);
	pPerson->SetEverCd4TestState(true);
	if(ReceiveCd4TestResult(pPerson))
		ScheduleCd4TestResult(pPerson);
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
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	ChargePreArtClinicCd4ResultVisit(pPerson);
	D(cout << "Cd4TestResult executed." << endl);
	pPerson->SetEverCD4TestResultState(true);
	if(pPerson->GetEligible()) {
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson);
	} else {
		D(cout << "Not eligible for ART." << endl);
		SchedulePreArtCd4Test(pPerson);
	}
	SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

ArtInitiation::ArtInitiation(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "ArtInitiation scheduled for day = " << Time << endl);
}

ArtInitiation::~ArtInitiation()
{}

bool ArtInitiation::CheckValid()
{
	cout << boolalpha << pPerson->GetArtInitiationState() << " = ART INITIATION STATE." << endl;
	if(!pPerson->GetArtInitiationState())
		return pPerson->Alive();
	else
		return false;
}

void ArtInitiation::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	D(cout << "ArtInitiation executed." << endl);
	if(!pPerson->GetArtAdherenceState())
		D(cout << "NON-ADHERER to Art." << endl);
	pPerson->SetArtInitiationState(true,GetTime());
	ScheduleCd4Update(pPerson);
	ScheduleWhoUpdate(pPerson);
	ScheduleArtDropout(pPerson);
	cout << boolalpha << pPerson->GetEverArt() << " = EVER ART." << endl;
}

/////////////////////
/////////////////////

ArtDropout::ArtDropout(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "ArtDropout scheduled for day = " << Time << endl);
}

ArtDropout::~ArtDropout()
{}

bool ArtDropout::CheckValid()
{
	return pPerson->Alive();
}

void ArtDropout::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);	
	D(cout << "ArtDropout executed." << endl);
	pPerson->SetArtInitiationState(false,GetTime());
	ScheduleCd4Update(pPerson);
	ScheduleWhoUpdate(pPerson);
}

/////////////////////
/////////////////////
