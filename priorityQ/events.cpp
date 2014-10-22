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
	
	pPerson->Kill(GetTime());
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
	pPerson->CheckHiv(GetTime());
	cout << GetTime() << endl;
}

/////////////////////
/////////////////////

Cd4Decline::Cd4Decline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Cd4Decline::~Cd4Decline()
{}

bool Cd4Decline::CheckValid()
{
	return pPerson->Alive();
}

void Cd4Decline::Execute()
{
	cout << "Cd4Decline executed." << endl;
	cout << "\tCd4Decline from " << pPerson->GetCurrentCd4() << " to ";
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()-1);
	cout << pPerson->GetCurrentCd4() << endl;
		//ScheduleCd4Update(pPerson);
	pPerson->AssignHivDeathDate();
}

/////////////////////
/////////////////////

Cd4Recover::Cd4Recover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Cd4Recover::~Cd4Recover()
{}

bool Cd4Recover::CheckValid()
{
	return true;
}

void Cd4Recover::Execute()
{
	cout << "Cd4Recover executed." << endl;
}

/////////////////////
/////////////////////

WhoDecline::WhoDecline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

WhoDecline::~WhoDecline()
{}

bool WhoDecline::CheckValid()
{
	return true;
}

void WhoDecline::Execute()
{
	cout << "WhoDecline executed." << endl;
}

/////////////////////
/////////////////////

WhoRecover::WhoRecover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

WhoRecover::~WhoRecover()
{}

bool WhoRecover::CheckValid()
{
	return true;
}

void WhoRecover::Execute()
{
	cout << "WhoRecover executed." << endl;
}

/////////////////////
/////////////////////
