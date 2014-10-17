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
#include "event.h"
#include "events.h"
#include "eventQ.h"

extern eventQ * theQ;

cohort::cohort(const unsigned int Size, const unsigned int StartTime) :
cohortSize(Size),
cohortStartTime(StartTime)
{
	event * newEvent = new CohortStart(this,cohortStartTime);
	theQ->AddEvent(newEvent);
}

cohort::~cohort()
{}

unsigned int cohort::GetCohortSize() const
{
	return cohortSize;
}

void cohort::PushToVector(person * const thePerson)
{
	cohortContainer.push_back(thePerson);
}

void cohort::GenerateCohort(const double Time) // Having these as constant arguments should not cause any issues.
{
	for(size_t i = 0; i < cohortSize; i++)
		NewPerson(Time);
}

void cohort::NewPerson(const double Time)
{
	person * thePerson = new person(Time);
	PushToVector(thePerson);
}