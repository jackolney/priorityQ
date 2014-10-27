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

extern eventQ * theQ;

/////////////////////
/////////////////////

void UpdateDaly(person * const thePerson)
{
//	dalyWeight_Cd4_3;
//	dalyWeight_Cd4_2;
//	dalyWeight_Cd4_1;
//	dalyWeightArt;
//	
//	/* Daly calculation */
//	double inc_hiv_time = 0;
//	
//		//time_hiv is an extern variable that calculates continuously the time elapsed between events... why not do that in the eventQ? DUH!
//
//		//Set time_hiv initially
//	if(theQ->GetTime() == thePerson->GetSeroconversionDay())
//		time_hiv = theQ->GetTime(); //but this == SeroconversionDay?
//
//		//Update time_hiv and set incremental time
//	if(theQ->GetTime() != thePerson->GetSeroconversionDay())
//		{
//		inc_hiv_time = theQ->GetTime() - thePerson->GetSeroconversionDay();
//		time_hiv = eventQ.top();
//		}
//		//ASSIGN DALY's
//	if(art == 0 && art_not_suppressed == 0)
//		{
//		if(cd4_current >= 3 && cd4_current < 5)
//			{
//			DALY = DALY + ((inc_hiv_time / 365.25) * daly_cost_cd4_3);
//			}
//		else if(cd4_current == 2)
//			{
//			DALY = DALY + ((inc_hiv_time / 365.25) * daly_cost_cd4_2);
//			}
//		else if(cd4_current == 1)
//			{
//			DALY = DALY + ((inc_hiv_time / 365.25) * daly_cost_cd4_1);
//			}
//		}
//	else if(art == 1 || art_not_suppressed == 1)
//		{
//		DALY = DALY + ((inc_hiv_time / 365.25) * daly_cost_art);
//		}
	
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
