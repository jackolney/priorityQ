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
		if((theQ->GetTime() - thePerson->GetHivDeathDate()) <= 365.35)
			thePerson->SetDalys((theQ->GetTime() - thePerson->GetHivDeathDate()) / 365.25);
		else
			thePerson->SetDalys(1);
	}
}

/////////////////////
/////////////////////

void WriteDaly(person * const thePerson)
{
	UpdateDaly(thePerson);
	
	/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
	double yr [20];
	for(size_t i = 0; i<20; i++)
		yr[i] = 14975.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() >= yr[i])
		i++;
	
	if(theQ->GetTime() > 14610)
		theDALY[i] += thePerson->GetDalys(); //+= should specify that DALYs can accumulate.
	
	thePerson->ResetDalys();
}

/////////////////////
/////////////////////
