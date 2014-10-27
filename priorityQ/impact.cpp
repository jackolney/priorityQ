//
//  impact.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "impact.h"
#include "person.h"
#include "toolbox.h"
#include "eventQ.h"
#include "output.h"

using namespace std;

extern eventQ * theQ;

/////////////////////
/////////////////////

void SeedDaly(person * const thePerson)
{
	double yr [21];
	for(size_t i = 0; i < 21; i++) {
		yr[i] = 14610 + (i * 365.25);
		new Daly(thePerson,yr[i]);
	}
}

/////////////////////
/////////////////////

void UpdateDaly(person * const thePerson)
{
	/* Daly calculation for within a year. */
	if(thePerson->Alive()) {
		if(thePerson->GetArtInitiationState())
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeightArt);
		else if(thePerson->GetCurrentCd4() >= 3)
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_3);
		else if(thePerson->GetCurrentCd4() == 2)
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_2);
		else if(thePerson->GetCurrentCd4() == 1)
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_1);
	}
	else if(theQ->GetTime() <= thePerson->GetNatDeathDate()) {
		if((theQ->GetTime() - thePerson->GetHivDeathDate()) <= 365.35) {
				thePerson->SetDalys((theQ->GetTime() - thePerson->GetHivDeathDate()) / 365.25);
				cout << "GetTime() = " << theQ->GetTime() << endl;
				cout << "GetHivDeathDate() = " << thePerson->GetHivDeathDate() << endl;
				cout << "theQ->GetTime() - thePerson->GetHivDeathDate() = " << theQ->GetTime() - thePerson->GetHivDeathDate() << endl;
		}
		else
			thePerson->SetDalys(1);
	}
	
	cout << "Incremental time = " << theQ->GetIncrementalTime() << endl;
	cout << "\t\t\t\t\t\t\t\t\t\tiDALY = " << thePerson->GetDalys() << endl;
	
		//Something odd going on with a negative value here an there around hivDeathDate??
	
}

/////////////////////
/////////////////////

Daly::Daly(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	
}

Daly::~Daly()
{}

bool Daly::CheckValid()
{
	return true;
}

void Daly::Execute()
{
//	/* Zero DALYs at the beginning of 2010 */ //bit redundant now.
//	if(theQ->GetTime() == 14610)
//		iDALY = 0;
	
	UpdateDaly(pPerson);
	
	/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
	double yr [20];
	
	for(size_t i = 0; i<20; i++)
		yr[i] = 14975.25 + (i * 365.25);


	unsigned int i = 0;

	while(theQ->GetTime() > yr[i])
		i++;

	theDALY[i] = pPerson->GetDalys();
	
	cout << "\t\t\t\t\t\t\t\t\t\ttheTime = " << theQ->GetTime() << endl;
	cout << "\t\t\t\t\t\t\t\t\t\ttheyr[i] = " << yr[i] << endl;
	cout << "\t\t\t\t\t\t\t\t\t\tiDALY = " << pPerson->GetDalys()<< endl;
	cout << "\t\t\t\t\t\t\t\t\t\ttheDALY = " << theDALY[i] << endl;
	
	pPerson->ResetDalys();
	
	cout << "\t\t\t\t\t\t\t\t\t\tiDALY (should be ZERO) = " << pPerson->GetDalys() << endl;
	
	//This event will be scheduled on 1st Jan 2010 and each year thereafter.
	//It will first write a huge value to the first value in the array on 1st Jan 2010 and then overwrite it in 2011.
}

/////////////////////
/////////////////////
