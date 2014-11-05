//
//  discount.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "discount.h"
#include "toolbox.h"

using namespace std;

/////////////////////
/////////////////////

void SeedDiscount(person * const thePerson)
{
	for(size_t i=0;i<19;i++)
		if(thePerson->GetBirthDay() <= 14975.25 + (i * 365.25))
			new AnnualDiscount(thePerson,14975.25 + (i * 365.25));
		else
			Discount(thePerson);
}

/////////////////////
/////////////////////

AnnualDiscount::AnnualDiscount(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

AnnualDiscount::~AnnualDiscount()
{}

bool AnnualDiscount::CheckValid()
{
	return pPerson->Alive();
}

void AnnualDiscount::Execute()
{
	Discount(pPerson);
}

/////////////////////
/////////////////////

void Discount(person * const thePerson)
{
	/* DALY weights */
	dalyWeight_Cd4_3 *= 0.94;
	dalyWeight_Cd4_2 *= 0.94;
	dalyWeight_Cd4_1 *= 0.94;
	dalyWeightArt *= 0.94;
	
	/* Hiv care unit costs */
	hctVisitCost *= 0.94;
	rapidHivTestCost *= 0.94;
	preArtClinicVisitCost *= 0.94;
	labCd4TestCost *= 0.94;
	pocCd4TestCost *= 0.94;
	annualArtCost *= 0.94;
	
	/* Intervention costs */
	annualAdherenceCost *= 0.94;
	outreachCost *= 0.94;
}

/////////////////////
/////////////////////