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
#include "outputUpdate.h"
#include "cost.h"

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
	pCohort->GenerateCohort(GetTime());
}

/////////////////////
/////////////////////

VectorUpdate::VectorUpdate(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "VectorUpdate on day = " << Time << endl);
	pPerson->SetVectorUpdateDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

VectorUpdate::~VectorUpdate()
{}

bool VectorUpdate::CheckValid()
{
	if(pPerson->GetVectorUpdateDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void VectorUpdate::Execute()
{
	pPerson->UpdatePopulation();
}

/////////////////////
/////////////////////

Incidence::Incidence(population * const thePopulation, const double Time, const size_t theIndex) :
event(Time),
pPopulation(thePopulation),
index(theIndex)
{}

Incidence::~Incidence()
{}

bool Incidence::CheckValid()
{
	return true;
}

void Incidence::Execute()
{
	pPopulation->CalculateIncidence(index,GetTime());
}

/////////////////////
/////////////////////

BetaCalculation::BetaCalculation(population * const thePopulation, const double Time) :
event(Time),
pPopulation(thePopulation)
{
	D(cout << "BetaCalculation scheduled for = " << Time << endl);
}

BetaCalculation::~BetaCalculation()
{}

bool BetaCalculation::CheckValid()
{
	return true;
}

void BetaCalculation::Execute()
{
	pPopulation->CalculateBeta();
}

/////////////////////
/////////////////////

Infection::Infection(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetHivDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Infection::~Infection()
{}

bool Infection::CheckValid()
{
	return pPerson->Alive();
}

void Infection::Execute()
{
	pPerson->Hiv(GetTime());
}

/////////////////////
/////////////////////

PersonStart::PersonStart(population * const iPop, const double Time) :
event(Time),
pPop(iPop)
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
	new person(pPop,GetTime());
}

/////////////////////
/////////////////////

Death::Death(person * const thePerson, const double Time, const bool hivCause) :
event(Time),
pPerson(thePerson),
hivRelated(hivCause)
{
	if(hivCause)
		pPerson->SetHivDeathDate(Time);
}

Death::~Death()
{}

bool Death::CheckValid()
{
	if(hivRelated) {
		if(pPerson->GetHivDeathDate() == GetTime())
			return pPerson->Alive();
		else
			return false;
	} else if(pPerson->Alive()) {
		return true;
	} else {
		delete pPerson;
		return false;
	}
}

void Death::Execute()
{
	UpdateDaly(pPerson,GetTime());
	WriteCost(pPerson,GetTime());
	pPerson->Kill(GetTime(),hivRelated);
	WriteCare(pPerson,GetTime());
	WriteDeath(pPerson,GetTime());
	if(hivRelated) {
		D(cout << "Death executed (HIV-related)." << endl);
		WriteAidsDeath(pPerson,GetTime());
		WriteClinic(pPerson,GetTime());
	}
	else {
		D(cout << "Death executed (Natural)." << endl);
		delete pPerson;
	}
}

/////////////////////
/////////////////////

Cd4Decline::Cd4Decline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetCd4DeclineDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	UpdateDaly(pPerson,GetTime());
	D(cout << "Cd4Decline executed." << endl);
	D(cout << "\tCd4Decline from " << pPerson->GetCurrentCd4() << " to ");
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()-1);
	D(cout << pPerson->GetCurrentCd4() << endl);
	ScheduleCd4Update(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	pPerson->UpdateInfectiousnessArray();
}

/////////////////////
/////////////////////

Cd4Recover::Cd4Recover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetCd4RecoverDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Cd4Recover::~Cd4Recover()
{}

bool Cd4Recover::CheckValid()
{
	if(pPerson->GetArtInitiationState() && pPerson->GetArtAdherenceState() && pPerson->GetCd4RecoverDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void Cd4Recover::Execute()
{
	UpdateDaly(pPerson,GetTime());
	D(cout << "Cd4Recover executed." << endl);
	D(cout << "\tCd4Recover from " << pPerson->GetCurrentCd4() << " to ");
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()+1);
	D(cout << pPerson->GetCurrentCd4() << endl);
	ScheduleCd4Update(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	pPerson->UpdateInfectiousnessArray();
}

/////////////////////
/////////////////////

WhoDecline::WhoDecline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetWhoDeclineDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
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
	UpdateDaly(pPerson,GetTime());
	D(cout << "WhoDecline executed." << endl);
	D(cout << "\tWhoDecline from " << pPerson->GetCurrentWho() << " to ");
	pPerson->SetCurrentWhoStage(pPerson->GetCurrentWho()+1);
	D(cout << pPerson->GetCurrentWho() << endl);
	ScheduleWhoUpdate(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	if(pPerson->GetCurrentWho() > 2)
		SchedulePictHivTest(pPerson,GetTime());
}

/////////////////////
/////////////////////

WhoRecover::WhoRecover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetWhoRecoverDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }	
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
	UpdateDaly(pPerson,GetTime());
	D(cout << "WhoRecover executed." << endl);
	D(cout << "\tWhoRecover from " << pPerson->GetCurrentWho() << " to ");
	pPerson->SetCurrentWhoStage(pPerson->GetCurrentWho()-1);
	D(cout << pPerson->GetCurrentWho() << endl);
	ScheduleWhoUpdate(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
}

/////////////////////
/////////////////////
