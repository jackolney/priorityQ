//
//  cascadeEvents.h
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__cascadeEvents__
#define __priorityQ__cascadeEvents__

#include <stdio.h>
#include "person.h"
#include "cohort.h"
#include "event.h"

/////////////////////
/////////////////////

class VctHivTest : public event {
public:
	VctHivTest(person * const thePerson, const double Time); //constructor
	~VctHivTest(); //destructor
	
	/* Methods */
	bool CheckValid();
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
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class ArtInitiation : public event {
public:
	ArtInitiation(person * const thePerson, const double Time); // constructor
	~ArtInitiation(); //destructor
	
	/* Methodss */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////


#endif /* defined(__priorityQ__cascadeEvents__) */
