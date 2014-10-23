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
#include "event.h"
#include "person.h"
#include "update.h"
#include "cohort.h"

using namespace std;

/////////////////////
/////////////////////

HctHivTest::HctHivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetHctHivTestDate(Time);
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
		pPerson->SetDiagnosedState(true);
		D(cout << "Diagnosed as HIV-positive." << endl);
			//Linkage probability -> ScheduleCd4Test();
			//PrevDiagLinkage stuff?
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
}

VctHivTest::~VctHivTest()
{}

bool VctHivTest::CheckValid()
{
	if(pPerson->GetVctHivTestDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
		//If returning false, reschedule next VctHivTest();
}

void VctHivTest::Execute()
{
	D(cout << "VctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true);
		D(cout << "Diagnosed as HIV-positive." << endl);
			//Linkageprobability.. -> ScheduleCd4Test();
	}
	UpdateEvents(pPerson);
	//ScheduleVctHivTest()
};

/////////////////////
/////////////////////

Cd4Test::Cd4Test(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Cd4Test::~Cd4Test()
{}

bool Cd4Test::CheckValid()
{
	return true;
}

void Cd4Test::Execute()
{
	D(cout << "Cd4Test executed." << endl);
	pPerson->SetCd4TestState(true);
	UpdateEvents(pPerson);
};

/////////////////////
/////////////////////

ArtInitiation::ArtInitiation(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

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
