//
//  incidence.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "incidence.h"


Incidence::Incidence()
{}

Incidence::~Incidence()
{}

void Incidence::UpdateIncidence(person * const thePerson)
{
	if(thePerson->GetSeroStatus())
		pIncidence.push_back(thePerson);
}

void Incidence::ResetIncidence()
{
	pIncidence.clear();
}

size_t Incidence::GetIncidenceVectorSize() const
{
	return pIncidence.size();
}

