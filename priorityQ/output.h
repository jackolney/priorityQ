	//
	//  output.h
	//  priorityQ
	//
	//  Created by Jack Olney on 28/10/2014.
	//  Copyright (c) 2014 Jack Olney. All rights reserved.
	//

#ifndef __priorityQ__output__
#define __priorityQ__output__

#include <stdio.h>
#include "person.h"
#include "event.h"

void SeedOutput(person * const thePerson);

/////////////////////
/////////////////////

class Output : public event { //For reporting Outputs annually.
public:
	Output(person * const thePerson, const double Time); //constructor
	~Output(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

void CreateCareExperienceArray();

void CreateDalyArray();

void CreateCostArray();

void FillOutCareExperienceArray(person * const thePerson, const double theTime);

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__output__) */
