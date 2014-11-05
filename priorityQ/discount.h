//
//  discount.h
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__discount__
#define __priorityQ__discount__

#include <stdio.h>
#include "event.h"
#include "person.h"

/////////////////////
/////////////////////

void SeedDiscount(person * const thePerson);

/////////////////////
/////////////////////

class AnnualDiscount : public event {
public:
	AnnualDiscount(person * const thePerson, const double Time); //constructor
	~AnnualDiscount(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

void Discount(person * const thePerson);

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__discount__) */
