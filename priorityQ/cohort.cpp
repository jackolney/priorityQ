//
//  cohort.cpp
//  priorityQ
//
//  Created by Jack Olney on 15/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "cohort.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "eventQ.h"
#include "rng.h"

extern Rng * theRng;
extern eventQ * theQ;

cohort::cohort(population * const thePop, const unsigned int Size, const unsigned int StartTime) :
iPop(thePop),
cohortSize(Size),
cohortStartTime(StartTime)
{
	new CohortStart(this,cohortStartTime);
	D(cout << "New cohort initialised. Cohort of " << Size << " people will be released into the wild on day = " << StartTime << endl);
}

cohort::~cohort()
{}

unsigned int cohort::GetCohortSize() const
{
	return cohortSize;
}

void cohort::GenerateCohort()
{
	D(cout << "Individuals (n=" << cohortSize << ") being seeded into the model." << endl);
	for(size_t i = 0; i < cohortSize; i++)
		ScheduleNewPerson(theRng->doub() * 365.25 + theQ->GetTime()); //The arguement here specifies when an individual will enter the model.
}

void cohort::ScheduleNewPerson(const double Time)
{
	D(cout << "ScheduleNewPerson on " << Time << endl);
	new PersonStart(this,Time);
}

void cohort::GenerateNewPerson()
{
	D(cout << "GenerateNewPerson on " << theQ->GetTime() << endl);
	new person(iPop,theQ->GetTime());
}
