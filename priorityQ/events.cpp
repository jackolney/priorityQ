//
//  events.cpp
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "events.h"
#include "event.h"
#include "person.h"
#include "update.h"
#include "cohort.h"

using namespace std;

/////////////////////
/////////////////////

CohortStart::CohortStart(cohort * const iCohort, const double Time) :
event(Time),
pCohort(iCohort)
{}

CohortStart::~CohortStart()
{}

bool CohortStart::CheckValid()
{
	return true;
}

void CohortStart::Execute()
{
	D(cout << "CohortStart executed." << endl);
	pCohort->GenerateCohort(); //IDIOT - WRONG POINTER!!!!
}

/////////////////////
/////////////////////

PersonStart::PersonStart(cohort * const iCohort, const double Time) :
event(Time),
pCohort(iCohort)
{}

PersonStart::~PersonStart()
{}

bool PersonStart::CheckValid()
{
	return true;
}

void PersonStart::Execute()
{
	D(cout << "PersonStart executed." << endl);
	pCohort->GenerateNewPerson();
}

/////////////////////
/////////////////////

Death::Death(person * const thePerson, const double Time, const bool hivCause) :
event(Time),
pPerson(thePerson),
hivRelated(hivCause)
{}

Death::~Death()
{}

bool Death::CheckValid()
{
	return pPerson->Alive();
}

void Death::Execute()
{
	if(hivRelated)
		D(cout << "Death executed (HIV-related)." << endl);
	else
		D(cout << "Death executed (Natural)." << endl);
	
	pPerson->Kill(eventTime);
}

/////////////////////
/////////////////////


HivIncidence::HivIncidence(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

HivIncidence::~HivIncidence()
{}

bool HivIncidence::CheckValid()
{
	if(pPerson->Alive() && !pPerson->GetSeroStatus())
		return true;
	else
		return false;
}

void HivIncidence::Execute()
{
	pPerson->CheckHiv(eventTime);
}

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

