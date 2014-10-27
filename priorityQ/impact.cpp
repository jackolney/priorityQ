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

void UpdateDaly(person * const thePerson)
{
	/* Daly calculation for within a year. */
	if(theQ->GetTime() >= 14610) {
	if(thePerson->GetArtInitiationState())
		iDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeightArt;
	else if(thePerson->GetCurrentCd4() >= 3)
		iDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_3;
	else if(thePerson->GetCurrentCd4() == 2)
		iDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_2;
	else if(thePerson->GetCurrentCd4() == 1)
		iDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_1;
	}
	
	cout << "\t\t\t\t\t\t\t\t\t\tiDALY = " << iDALY << endl;
	
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
	return pPerson->Alive();
}

void Daly::Execute()
{
	/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
	double yr [20];
	
	for(size_t i = 0; i<20; i++)
		yr[i] = 14975.25 + (i * 365.25);


	unsigned int i = 0;

	while(i < yr[i])
		i++;

	theDALY[i] = iDALY;

//	iDALY = 0;
	
		//Update theDALY for the particular year.
		//Zero's iDALY.
}

/////////////////////
/////////////////////
