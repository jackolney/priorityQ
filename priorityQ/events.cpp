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
#include "cascadeUpdate.h"
#include "cohort.h"
#include "impact.h"
#include "output.h"
#include "transmission.h"

extern Transmission * theTrans;

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
	pCohort->GenerateCohort();
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
{
	if(hivCause)
		thePerson->SetHivDeathDate(Time);
}

Death::~Death()
{}

bool Death::CheckValid()
{
	if(hivRelated)
		if(pPerson->GetHivDeathDate() == GetTime())
			return pPerson->Alive();
		else
			return false;
	else
		return pPerson->Alive();
}

void Death::Execute()
{
	if(hivRelated)
		D(cout << "Death executed (HIV-related)." << endl);
	else
		D(cout << "Death executed (Natural)." << endl);
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	pPerson->Kill(GetTime(),hivRelated);
	theTrans->UpdateVector(pPerson);
	WriteCare(pPerson,GetTime());
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
	UpdateAge(pPerson);
	pPerson->CheckHiv(GetTime());
}

/////////////////////
/////////////////////

Cd4Decline::Cd4Decline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetCd4DeclineDate(Time);
}

Cd4Decline::~Cd4Decline()
{}

bool Cd4Decline::CheckValid()
{
	if((!pPerson->GetArtInitiationState() || (pPerson->GetArtInitiationState() && !pPerson->GetArtAdherenceState())) && pPerson->GetCd4DeclineDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void Cd4Decline::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	D(cout << "Cd4Decline executed." << endl);
	D(cout << "\tCd4Decline from " << pPerson->GetCurrentCd4() << " to ");
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()-1);
	D(cout << pPerson->GetCurrentCd4() << endl);
	ScheduleCd4Update(pPerson);
	pPerson->AssignHivDeathDate();
	theTrans->UpdateVector(pPerson);
}

/////////////////////
/////////////////////

Cd4Recover::Cd4Recover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetCd4RecoverDate(Time);
}

Cd4Recover::~Cd4Recover()
{}

bool Cd4Recover::CheckValid()
{
	if(pPerson->GetArtInitiationState() && pPerson->GetArtAdherenceState() && pPerson->GetCd4RecoverDate()	== GetTime())
		return pPerson->Alive();
	else
		return false;
}

void Cd4Recover::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	D(cout << "Cd4Recover executed." << endl);
	D(cout << "\tCd4Recover from " << pPerson->GetCurrentCd4() << " to ");
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()+1);
	D(cout << pPerson->GetCurrentCd4() << endl);
	ScheduleCd4Update(pPerson);
	pPerson->AssignHivDeathDate();
	theTrans->UpdateVector(pPerson);
}

/////////////////////
/////////////////////

WhoDecline::WhoDecline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetWhoDeclineDate(Time);
}

WhoDecline::~WhoDecline()
{}

bool WhoDecline::CheckValid()
{
	if(pPerson->GetWhoDeclineDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void WhoDecline::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);
	D(cout << "WhoDecline executed." << endl);
	D(cout << "\tWhoDecline from " << pPerson->GetCurrentWho() << " to ");
	pPerson->SetCurrentWhoStage(pPerson->GetCurrentWho()+1);
	D(cout << pPerson->GetCurrentWho() << endl);
	ScheduleWhoUpdate(pPerson);
	pPerson->AssignHivDeathDate();
	if(pPerson->GetCurrentWho() > 2)
		SchedulePictHivTest(pPerson);
}

/////////////////////
/////////////////////

WhoRecover::WhoRecover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetWhoRecoverDate(Time);
}

WhoRecover::~WhoRecover()
{}

bool WhoRecover::CheckValid()
{
	if(pPerson->GetArtInitiationState() && pPerson->GetArtAdherenceState() && pPerson->GetWhoRecoverDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void WhoRecover::Execute()
{
	UpdateAge(pPerson);
	UpdateDaly(pPerson);	
	D(cout << "WhoRecover executed." << endl);
	D(cout << "\tWhoRecover from " << pPerson->GetCurrentWho() << " to ");
	pPerson->SetCurrentWhoStage(pPerson->GetCurrentWho()-1);
	D(cout << pPerson->GetCurrentWho() << endl);
	ScheduleWhoUpdate(pPerson);
	pPerson->AssignHivDeathDate();
}

/////////////////////
/////////////////////
