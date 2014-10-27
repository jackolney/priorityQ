//
//  impact.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "impact.h"
#include "person.h"

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
}

/////////////////////
/////////////////////
