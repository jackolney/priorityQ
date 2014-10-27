//
//  cost.h
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__cost__
#define __priorityQ__cost__

#include <stdio.h>
#include "person.h"
#include "event.h"

/////////////////////
/////////////////////

extern double theCOST [20];

extern double * pTheCOST;

/////////////////////
/////////////////////

void SeedCost(person * const thePerson);

/////////////////////
/////////////////////

void ChargeHctVisit(person * const thePerson);

//void ChargeHctVisitPoc(person * const thePerson);

void ChargeVctPictHivTest(person * const thePerson);

//void ChargeVctPictClinicVisitPoc(person * const thePerson);

void ChargePreArtClinicVisit(person * const thePerson);

//void ChargePreArtClinicVisitPoc(person * const thePerson);

void ChargePreArtClinicResultVisit(person * const thePerson);

void ChargeArtCare(person * const thePerson);

/////////////////////
/////////////////////

class Cost : public	event { //For reporting costs annually.
public:
	Cost(person * const thePerson, const double Time); //constructor
	~Cost(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

#endif /* defined(__priorityQ__cost__) */
