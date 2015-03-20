//
//  impact.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "impact.h"
#include "macro.h"
#include "person.h"
#include "toolbox.h"
#include "eventQ.h"

using namespace std;

extern eventQ * theQ;
extern double * theDALY;

/////////////////////
/////////////////////

void UpdateDaly(person * const thePerson, const double theTime)
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
	else if(theTime <= thePerson->GetNatDeathDate()) {
		if((theTime - thePerson->GetHivDeathDate()) <= 365.35)
			thePerson->SetDalys((theTime - thePerson->GetHivDeathDate()) / 365.25);
		else
			thePerson->SetDalys(1);
	}
}

/////////////////////
/////////////////////

void WriteDaly(person * const thePerson, const size_t theIndex)
{
	UpdateDaly(thePerson,(theIndex + 1) * 365.25);
	
	if((theIndex + 1) * 365.25 > 14610)
		theDALY[theIndex - 40] += thePerson->GetDalys();
	
	thePerson->ResetDalys();
}

/////////////////////
/////////////////////
