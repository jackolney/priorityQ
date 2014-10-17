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
	cout << "New cohort initialised. Cohort will be released into the wild on day = " << StartTime << endl;
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

void cohort::GenerateCohort() // Having these as constant arguments should not cause any issues.
{
	cout << "Individuals being seeded into the model." << endl;
	for(size_t i = 0; i < cohortSize; i++)
		NewPerson(theQ->GetTime()); //The arguement here specifies when an individual will enter the model.
}

void cohort::NewPerson(const double Time)
{
	cout << "New guy entering the model." << endl;
	person * thePerson = new person(Time);
	PushToVector(thePerson);
}
