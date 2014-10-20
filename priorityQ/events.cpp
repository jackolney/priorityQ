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

void PersonStart::Execute()
{
	D(cout << "PersonStart executed." << endl);
	pCohort->GenerateNewPerson();
}

/////////////////////
/////////////////////

Death::Death(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Death::~Death()
{}

void Death::Execute()
{
	D(cout << "Death executed." << endl);
	pPerson->Kill(eventTime);
}

/////////////////////
/////////////////////

HivTest::HivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

HivTest::~HivTest()
{}

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

void Cd4Test::Execute()
{
	D(cout << "Cd4Test executed." << endl);
	pPerson->SetCd4TestState(true);
	UpdateEvents(pPerson);
};
