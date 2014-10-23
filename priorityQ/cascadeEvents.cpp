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
	D(cout << "VctHivTest scheduled for day = " << Time << endl);
}

VctHivTest::~VctHivTest()
{}

bool VctHivTest::CheckValid()
{
	if(pPerson->GetVctHivTestDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
	//Schedule next Vct test here - regardless of if ValidorNot;
}

void VctHivTest::Execute()
{
	D(cout << "VctHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true);
		D(cout << "Diagnosed as HIV-positive." << endl);
		
		//Linkage to Care
//		if(VctLinkage())
//			new Cd4Test(
	}
	UpdateEvents(pPerson);
};

/////////////////////
/////////////////////

PictHivTest::PictHivTest(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	thePerson->SetVctHivTestDate(Time);
	D(cout << "PictHivTest scheduled for day = " << Time << endl);
}

PictHivTest::~PictHivTest()
{}

bool PictHivTest::CheckValid()
{
	if(pPerson->GetPictHivTestDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
	//Schedule next Pict test here - regardless of if ValidorNot;
}

void PictHivTest::Execute()
{
	D(cout << "PictHivTest executed." << endl);
	if(pPerson->GetSeroStatus()) {
		pPerson->SetDiagnosedState(true);
		D(cout << "Diagnosed as HIV-positive." << endl);
			//Linkage probability -> ScheduleCd4Test();
	}
	UpdateEvents(pPerson);
}

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
	pPerson->SetEverCd4TestState(true);
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
