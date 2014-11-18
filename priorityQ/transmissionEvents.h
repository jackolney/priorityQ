//
//  transmissionEvents.h
//  priorityQ
//
//  Created by Jack Olney on 18/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__transmissionEvents__
#define __priorityQ__transmissionEvents__

#include <stdio.h>
#include "person.h"
#include "population.h"
#include "event.h"

class PopulateTransmissionProbabilityVector : public event {
public:
	PopulateTransmissionProbabilityVector(person * const thePerson, const double Time); //constructor
	~PopulateTransmissionProbabilityVector(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

class BetaCalculation : public event {
public:
	BetaCalculation(const double Time); //constructor
	~BetaCalculation(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
};

#endif /* defined(__priorityQ__transmissionEvents__) */
