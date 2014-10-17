//
//  events.h
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__events__
#define __priorityQ__events__

#include <stdio.h>
#include "person.h"
#include "cohort.h"
#include "event.h"

/////////////////////
/////////////////////

class CohortStart : public event {
public:
	CohortStart(cohort * const iCohort, const double Time); //constructor
	~CohortStart(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	cohort * const pCohort; //Pointer to cohort.
};

/////////////////////
/////////////////////

class PersonStart : public event {
public:
	PersonStart(cohort * const iCohort, const double Time); //constructor
	~PersonStart(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	cohort * const pCohort;
};


/////////////////////
/////////////////////

class Death : public event {
public:
	Death(person * const thePerson, const double Time); //constructor
	~Death(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	person * const pPerson; // pPerson here is the pointer to the relevant person that will experience the event.
};

/////////////////////
/////////////////////

class HivTest : public event {
public:
	HivTest(person * const thePerson, const double Time); //constructor
	~HivTest(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	person * const pPerson;
	
};

/////////////////////
/////////////////////

class Cd4Test : public event {
public:
	Cd4Test(person * const thePerson, const double Time); //constructor
	~Cd4Test(); //destructor
	
	/* Methods */
	void Execute();
	
private:
	person * const pPerson;
	
};

/////////////////////
/////////////////////



#endif /* defined(__priorityQ__events__) */
