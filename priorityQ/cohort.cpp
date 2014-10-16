//
//  cohort.cpp
//  priorityQ
//
//  Created by Jack Olney on 15/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "cohort.h"
#include "person.h"

//extern person * thePerson;

cohort::cohort(const unsigned int Size) : cohortSize(Size)
{}

cohort::~cohort()
{}

unsigned int cohort::GetCohortSize() const
{
	return cohortSize;
}

void cohort::GenerateCohort(const double Time) // Having these as constant arguments should not cause any issues.
{
	for(size_t i = 0; i < cohortSize; i++)
		NewPerson(Time);
}

void cohort::NewPerson(const double Time)
{
	person * thePerson = new person(Time); //Not correct (yet).
	cohortContainer.push_back(thePerson);
}