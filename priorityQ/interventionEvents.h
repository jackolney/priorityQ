//
//  interventionEvents.h
//  priorityQ
//
//  Created by Jack Olney on 03/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__interventionEvents__
#define __priorityQ__interventionEvents__

#include <stdio.h>
#include "event.h"
#include "person.h"

/////////////////////
/////////////////////

class HctHivTest : public event {
public:
	HctHivTest(person * const thePerson, const double Time, const bool poc); //constructor
	~HctHivTest(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
	const bool pointOfCare;
};

/////////////////////
/////////////////////

class HctPocCd4Test : public event {
public:
	HctPocCd4Test(person * const thePerson, const double Time); //constructor
	~HctPocCd4Test(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class PreArtOutreach : public event {
public:
	PreArtOutreach(person * const thePerson, const double Time, const double theProb); //constructor
	~PreArtOutreach(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
	const double probReturn;
};

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__interventionEvents__) */
