//
//  interventionEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 03/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "toolbox.h"
#include "interventionEvents.h"
#include "interventionUpdate.h"
#include "update.h"
#include "impact.h"
#include "cost.h"
#include "rng.h"
#include "cascadeEvents.h"
#include "cascadeUpdate.h"
#include "eventQ.h"

using namespace std;

extern Rng * theRng;
extern eventQ * theQ;

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

/////////////////////
/////////////////////

HctHivTest::HctHivTest(person * const thePerson, const double Time, const bool poc) :
event(Time),
pPerson(thePerson),
pointOfCare(poc)
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
	UpdateDaly(pPerson);
	ChargeHctVisit(pPerson);
	D(cout << "HctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,1);
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(immediateArtFlag)
			ScheduleImmediateArt(pPerson);
		else if(pointOfCare)
			new HctPocCd4Test(pPerson,GetTime());
		else if(HctLinkage(pPerson))
			ScheduleInitialCd4TestAfterHct(pPerson);
		SchedulePictHivTest(pPerson);
	}
}

/////////////////////
/////////////////////

HctPocCd4Test::HctPocCd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "HctPocCd4Test scheduled for day = " << Time << endl);
}

HctPocCd4Test::~HctPocCd4Test()
{}

bool HctPocCd4Test::CheckValid()
{
	return pPerson->Alive();
}

void HctPocCd4Test::Execute()
{
	UpdateDaly(pPerson);
	ChargePocCd4Test(pPerson);
	D(cout << "HctPocCd4Test executed." << endl);
	pPerson->SetEverCd4TestState(true);
	pPerson->SetEverCd4TestResultState(true);
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson);
	else if(pPerson->GetEligible()) {
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson);
	} else {
		D(cout << "Not eligible for ART." << endl);
		if(HctLinkage(pPerson))
			ScheduleInitialCd4TestAfterHct(pPerson);
	}
	SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

PreArtOutreach::PreArtOutreach(person * const thePerson, const double Time, const double theProb) :
event(Time),
pPerson(thePerson),
probReturn(theProb)
{
	D(cout << "PreArtOutreach scheduled for day = " << Time << endl);
}

PreArtOutreach::~PreArtOutreach()
{}

bool PreArtOutreach::CheckValid()
{
	if(pPerson->GetDiagnosedState() && !pPerson->GetInCareState())
		return pPerson->Alive();
	else
		return false;
}

void PreArtOutreach::Execute()
{
	D(cout << "PreArtOutreach executed." << endl);
	ChargePreArtOutreach(pPerson);
	if(theRng->Sample(probReturn))
		new Cd4Test(pPerson,GetTime());
}

/////////////////////
/////////////////////

VctPocCd4Test::VctPocCd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "VctPocCd4Test scheduled for day = " << Time << endl);
}

VctPocCd4Test::~VctPocCd4Test()
{}

bool VctPocCd4Test::CheckValid()
{
	return pPerson->Alive();
}

void VctPocCd4Test::Execute()
{
	D(cout << "VctPocCd4Test executed." << endl);
	D(cout << "Entered care." << endl);
	UpdateDaly(pPerson);
	ChargePreArtClinicVisit(pPerson);
	ChargePocCd4Test(pPerson);
	pPerson->SetEverCd4TestState(true);
	pPerson->SetEverCd4TestResultState(true);
	pPerson->SetInCareState(true);
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson);
	else if(pPerson->GetEligible()) {
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson);
	} else {
		D(cout << "Not eligible for ART." << endl);
		if(SecondaryCd4Test(pPerson))
			SchedulePreArtCd4Test(pPerson);
	}
	SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

PocCd4Test::PocCd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "PocCd4Test scheduled for day = " << Time << endl);
}

PocCd4Test::~PocCd4Test()
{}

bool PocCd4Test::CheckValid()
{
	return pPerson->Alive();
	
}

void PocCd4Test::Execute()
{
	D(cout << "PocCd4Test executed." << endl);	
	UpdateDaly(pPerson);
	ChargePreArtClinicVisit(pPerson);
	ChargePocCd4Test(pPerson);
	pPerson->SetEverCd4TestState(true);
	pPerson->SetEverCd4TestResultState(true);
	pPerson->SetInCareState(true);
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson);
	else if(pPerson->GetEligible()) {
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson);
	} else {
		D(cout << "Not eligible for ART." << endl);
		if(SecondaryCd4Test(pPerson))
			SchedulePreArtCd4Test(pPerson);
	}
	SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

ArtOutreach::ArtOutreach(person * const thePerson, const double Time, const double theProb) :
event(Time),
pPerson(thePerson),
probReturn(theProb)
{
	D(cout << "ArtOutreach scheduled for day = " << Time << endl);
}

ArtOutreach::~ArtOutreach()
{}

bool ArtOutreach::CheckValid()
{
	if(pPerson->GetEverArt() && !pPerson->GetArtInitiationState())
		return pPerson->Alive();
	else
		return false;
}

void ArtOutreach::Execute()
{
	D(cout << "ArtOutreach executed." << endl);
	ChargeArtOutreach(pPerson);
	if(pPerson->GetArtCount() < 2 && theRng->Sample(probReturn)) {
		UpdateDaly(pPerson);
		if(!pPerson->GetArtAdherenceState()) { D(cout << "NON-ADHERER to Art." << endl); }
		pPerson->SetArtInitiationState(true,GetTime());
		ScheduleCd4Update(pPerson);
		ScheduleWhoUpdate(pPerson);
		ScheduleArtDropout(pPerson);
		pPerson->UpdateInfectiousnessArray();
	}
}

/////////////////////
/////////////////////