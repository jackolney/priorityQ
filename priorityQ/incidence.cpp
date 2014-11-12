//
//  incidence.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "incidence.h"
#include "incidenceEvents.h"

Incidence::Incidence()
{
	ScheduleIncidenceReset(this);
}

Incidence::~Incidence()
{}

void Incidence::UpdateIncidence(person * const thePerson)
{
	if(thePerson->GetSeroStatus())
		pIncidence.push_back(thePerson);
}


void Incidence::ScheduleIncidenceReset(Incidence * const theInc)
{
	for(size_t i=0;i<60;i++)
		new SeedIncidence(theInc,i * 365.25);
}

void Incidence::ResetIncidence()
{
	pIncidence.clear();
}

size_t Incidence::GetIncidenceVectorSize() const
{
	return pIncidence.size();
}
