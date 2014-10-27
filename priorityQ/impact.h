//
//  impact.h
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__impact__
#define __priorityQ__impact__

#include <stdio.h>
#include "event.h"
#include "person.h"

/////////////////////
/////////////////////

double theDALY [20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double * pTheDALY = theDALY;

/////////////////////
/////////////////////

void SeedDaly(person * const thePerson);

/////////////////////
/////////////////////

void UpdateDaly(person * const thePerson);

/////////////////////
/////////////////////

class Daly : public event { //For reporting DALYs annually.
public:
	Daly(person * const thePerson, const double Time); //constructor
	~Daly(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__impact__) */
