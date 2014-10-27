//
//  impact.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "impact.h"
#include "person.h"
#include "toolbox.h"
#include "eventQ.h"
#include "output.h"

extern eventQ * theQ;

/////////////////////
/////////////////////

void UpdateDaly(person * const thePerson)
{
//	dalyWeight_Cd4_3;
//	dalyWeight_Cd4_2;
//	dalyWeight_Cd4_1;
//	dalyWeightArt;

	/* Daly calculation */

	if(thePerson->GetArtInitiationState())
		theDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeightArt;
	else if(thePerson->GetCurrentCd4() >= 3)
		theDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_3;
	else if(thePerson->GetCurrentCd4() == 2)
		theDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_2;
	else if(thePerson->GetCurrentCd4() == 1)
		theDALY += (theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_1;
	
		//Change to iDALY.
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
		//Update iDALY for an individual.
	
		//Report DALYs for the year >> Save it somewhere >> zero iDALY.
}

/////////////////////
/////////////////////
