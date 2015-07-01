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
#include "rng.h"
#include "toolbox.h"

using namespace std;

extern Rng * theRng;

cohort::cohort(population * const thePop, const unsigned int StartTime, const unsigned int theSizeAdjustment) :
iPop(thePop),
cohortStartTime(StartTime),
sizeAdjustment(theSizeAdjustment)
{
	new CohortStart(this,cohortStartTime);
}

cohort::~cohort()
{}

void cohort::GenerateCohort(const double theTime)
{	
	if(theTime == 0) {
		for(size_t i = 0; i < 11252466 / sizeAdjustment; i++)
			ScheduleNewPerson(theTime + theRng->doub() * 365.25); // The arguement here specifies when an individual will enter the model.
	} else {
		/* Define birth rate array */
		const double BirthRate [66] = {0.050735,0.050762,0.050763,0.050725,0.050639,0.050505,0.050332,0.050129,0.049902,0.049646,0.049356,0.049024,0.04864,0.04819,0.047667,0.047039,0.046274,0.045375,0.044364,0.043278,0.042177,0.041129,0.040194,0.039417,0.038826,0.038438,0.03825,0.038211,0.03827,0.038389,0.038532,0.038668,0.038773,0.038825,0.0388,0.038676,0.038442,0.03811,0.037699,0.037218,0.036681,0.036104,0.035505,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904,0.034904};
		
		int i = 0;
		while(i * 365.25 < theTime && i < 66)
			i++;
		
		const int NewCohortSize = Round(iPop->GetPopulationSize() * BirthRate[i]);
		
		for(size_t j = 0; j < NewCohortSize; j++)
			ScheduleNewPerson(theRng->doub() * 365.25 + theTime); // The arguement here specifies when an individual will enter the model.
	}
	
	SelfDestruct(); // This kills the cohort instance.
}

void cohort::ScheduleNewPerson(const double Time)
{
	new PersonStart(iPop,Time);
}

void cohort::SelfDestruct()
{
	delete this;
}
