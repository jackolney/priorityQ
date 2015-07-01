//
//  cohort.h
//  priorityQ
//
//  Created by Jack Olney on 15/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__cohort__
#define __priorityQ__cohort__

#include <vector>
#include <stdio.h>
#include "person.h"
#include "population.h"

using namespace std;

class cohort {
public:
	cohort(population * const thePop, const unsigned int StartTime, const unsigned int theSizeAdjustment); //constructor
	~cohort(); //destructor
	
	/* methods */
	void GenerateCohort(const double theTime);
	void ScheduleNewPerson(const double Time);
	void SelfDestruct();
	
private:
	population * const iPop;
	unsigned int cohortStartTime; //Specifies the time that the cohort will enter the model.
	unsigned int sizeAdjustment;
	
};

#endif /* defined(__priorityQ__cohort__) */
