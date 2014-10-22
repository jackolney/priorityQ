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
	bool CheckValid();
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
	bool CheckValid();
	void Execute();
	
private:
	cohort * const pCohort;
};

/////////////////////
/////////////////////

class Death : public event {
public:
	Death(person * const thePerson, const double Time, const bool hivCause); //constructor
	~Death(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson; // pPerson here is the pointer to the relevant person that will experience the event.
	const bool hivRelated;
};

/////////////////////
/////////////////////

class HivIncidence : public event {
public:
	HivIncidence(person * const thePerson, const double Time); //constructor
	~HivIncidence(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

///////////////////////
///////////////////////

class Cd4Decline : public event {
public:
	Cd4Decline(person * const thePerson, const double Time); //constructor
	~Cd4Decline(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

///////////////////////
///////////////////////

class Cd4Recover : public event {
public:
	Cd4Recover(person * const thePerson, const double Time); //constructor
	~Cd4Recover(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

///////////////////////
///////////////////////

class WhoDecline : public event {
public:
	WhoDecline(person * const thePerson, const double Time); //constructor
	~WhoDecline(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

///////////////////////
///////////////////////

class WhoRecover : public event {
public:
	WhoRecover(person * const thePerson, const double Time); //constructor
	~WhoRecover(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

///////////////////////
///////////////////////

#endif /* defined(__priorityQ__events__) */
