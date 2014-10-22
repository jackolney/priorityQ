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

HivTest::HivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

HivTest::~HivTest()
{}

bool HivTest::CheckValid()
{
	if(pPerson->Alive())
		return true;
	else {
		Cancel();
		D(cout << "HivTest cancelled." << endl);
		return false;
	}
}

void HivTest::Execute()
{
	D(cout << "HivTest executed." << endl);
	pPerson->SetDiagnosedState(true);
	UpdateEvents(pPerson);
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
	UpdateEvents(pPerson);
}

/////////////////////
/////////////////////
