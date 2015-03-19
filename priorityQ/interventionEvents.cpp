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

using namespace std;

extern Rng * theRng;

/////////////////////
/////////////////////

SeedHct::SeedHct(person * const thePerson, const double Time, const bool poc) :
event(Time),
pPerson(thePerson),
pointOfCare(poc)
{
	D(cout << "Hct seeded for deployment on day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	ScheduleHctHivTest(pPerson,GetTime(),pointOfCare);
}

/////////////////////
/////////////////////

SeedPerpetualHct::SeedPerpetualHct(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "PerpetualHct seeded for deployment on day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

SeedPerpetualHct::~SeedPerpetualHct()
{}

bool SeedPerpetualHct::CheckValid()
{
	if(!pPerson->GetEverArt())
		return pPerson->Alive();
	else
		return false;
}

void SeedPerpetualHct::Execute()
{
	SchedulePerpetualHctHivTest(pPerson,GetTime());
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
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	UpdateDaly(pPerson,GetTime());
	ChargeHctVisit(pPerson);
	D(cout << "HctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true,1,GetTime());
		D(cout << "Diagnosed as HIV-positive." << endl);
		if(pointOfCare)
			new HctPocCd4Test(pPerson,GetTime());
		else if(HctLinkage(pPerson))
			ScheduleInitialCd4TestAfterHct(pPerson,GetTime());
		SchedulePictHivTest(pPerson,GetTime());
	}
}

/////////////////////
/////////////////////

HctPocCd4Test::HctPocCd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "HctPocCd4Test scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

HctPocCd4Test::~HctPocCd4Test()
{}

bool HctPocCd4Test::CheckValid()
{
	return pPerson->Alive();
}

void HctPocCd4Test::Execute()
{
	UpdateDaly(pPerson,GetTime());
	ChargePocCd4Test(pPerson);
	D(cout << "HctPocCd4Test executed." << endl);
	pPerson->SetEverCd4TestState(true);
	pPerson->SetEverCd4TestResultState(true);
	if(pPerson->GetEligible()) {
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson,GetTime());
	} else {
		D(cout << "Not eligible for ART." << endl);
		if(HctLinkage(pPerson))
			ScheduleInitialCd4TestAfterHct(pPerson,GetTime());
	}
	SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

PreArtOutreach::PreArtOutreach(person * const thePerson, const double Time, const double theProb) :
event(Time),
pPerson(thePerson),
probReturn(theProb)
{
	D(cout << "PreArtOutreach scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	UpdateDaly(pPerson,GetTime());
	ChargePreArtClinicVisit(pPerson);
	pPerson->SetEverCd4TestState(true);
	pPerson->SetEverCd4TestResultState(true);
	pPerson->SetInCareState(true,GetTime());
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson,GetTime());
	else if(pPerson->GetEligible()) {
		ChargePocCd4Test(pPerson);
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson,GetTime());
	} else {
		ChargePocCd4Test(pPerson);
		D(cout << "Not eligible for ART." << endl);
		if(SecondaryCd4Test(pPerson,GetTime()))
			SchedulePreArtCd4Test(pPerson,GetTime());
	}
	SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

PocCd4Test::PocCd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "PocCd4Test scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	UpdateDaly(pPerson,GetTime());
	ChargePreArtClinicVisit(pPerson);
	pPerson->SetEverCd4TestState(true);
	pPerson->SetEverCd4TestResultState(true);
	pPerson->SetInCareState(true,GetTime());
	if(immediateArtFlag)
		ScheduleImmediateArt(pPerson,GetTime());
	else if(pPerson->GetEligible()) {
		ChargePocCd4Test(pPerson);
		D(cout << "Eligible for ART." << endl);
		ScheduleArtInitiation(pPerson,GetTime());
	} else {
		ChargePocCd4Test(pPerson);
		D(cout << "Not eligible for ART." << endl);
		if(SecondaryCd4Test(pPerson,GetTime()))
			SchedulePreArtCd4Test(pPerson,GetTime());
	}
	SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

ArtOutreach::ArtOutreach(person * const thePerson, const double Time, const double theProb) :
event(Time),
pPerson(thePerson),
probReturn(theProb)
{
	D(cout << "ArtOutreach scheduled for day = " << Time << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }	
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
		UpdateDaly(pPerson,GetTime());
		if(!pPerson->GetArtAdherenceState()) { D(cout << "NON-ADHERER to Art." << endl); }
		pPerson->SetArtInitiationState(true,GetTime());
		ScheduleCd4Update(pPerson,GetTime());
		ScheduleWhoUpdate(pPerson,GetTime());
		ScheduleArtDropout(pPerson,GetTime());
		pPerson->UpdateInfectiousnessArray();
	}
}

/////////////////////
/////////////////////