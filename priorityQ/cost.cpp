//
//  cost.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "cost.h"
#include "person.h"
#include "toolbox.h"
#include "eventQ.h"

using namespace std;

extern eventQ * theQ;
extern double * theCOST;

/////////////////////
/////////////////////

void SeedCost(person * const thePerson)
{
	double yr [21];
	for(size_t i = 0; i < 21; i++) {
		yr[i] = 14610 + (i * 365.25);
		new Cost(thePerson,yr[i]);
	}
}

/////////////////////
/////////////////////

void ChargeHctVisit(person * const thePerson)
{
	thePerson->SetHctVisitCost(hctVisitCost);
	thePerson->SetRapidHivTestCost(rapidHivTestCost);
}

/////////////////////
/////////////////////

void ChargeVctPictHivTest(person * const thePerson)
{
	thePerson->SetRapidHivTestCost(rapidHivTestCost);
}

/////////////////////
/////////////////////

void ChargePreArtClinicVisit(person * const thePerson)
{
	thePerson->SetPreArtClinicVisitCost(preArtClinicVisitCost);
}

/////////////////////
/////////////////////

void ChargePreArtClinicCd4Test(person * const thePerson)
{
	thePerson->SetLabCd4Test(labCd4Test);
}

/////////////////////
/////////////////////

void ChargePreArtClinicCd4ResultVisit(person * const thePerson)
{
	thePerson->SetPreArtClinicVisitCost(preArtClinicVisitCost);
}

/////////////////////
/////////////////////

void ChargeArtCare(person * const thePerson)
{
	if(thePerson->GetArtInitiationState()) {
		if(thePerson->GetArtDay() <= 14610)
			thePerson->SetAnnualArtCost((((theQ->GetTime() - 14610) + thePerson->GetArtTime()) / 365.25) * annualArtCost);
		else
			thePerson->SetAnnualArtCost((((theQ->GetTime() - thePerson->GetArtDay()) + thePerson->GetArtTime()) / 365.25) * annualArtCost);
	} else
		thePerson->SetAnnualArtCost((thePerson->GetArtTime() / 365.25) * annualArtCost);
}

/////////////////////
/////////////////////

Cost::Cost(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Cost::~Cost()
{}

bool Cost::CheckValid()
{
	return pPerson->Alive();
}

void Cost::Execute()
{
	ChargeArtCare(pPerson);
	
	/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
	double yr [20];
	for(size_t i = 0; i<20; i++)
		yr[i] = 14975.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i])
		i++;
	
//	cout << pPerson->GetHctVisitCost() << " = GetHctVisitCost()" << endl;
//	cout << pPerson->GetRapidHivTestCost() << " = GetRapidHivTestCost()" << endl;
//	cout << pPerson->GetPreArtClinicVisitCost() << " = GetPreArtClinicVisitCost()" << endl;
//	cout << pPerson->GetLabCd4Test() << " = GetLabCd4Test()" << endl;
//	cout << pPerson->GetPocCd4Test() << " = GetPocCd4Test()" << endl;
//	cout << pPerson->GetAnnualArtCost() << " = GetAnnualArtCost()" << endl;
	
	if(GetTime() > 14610)
		theCOST[i] += pPerson->GetHctVisitCost() + pPerson->GetRapidHivTestCost() + pPerson->GetPreArtClinicVisitCost() + pPerson->GetLabCd4Test() + pPerson->GetPocCd4Test() + pPerson->GetAnnualArtCost();
	
	if(GetTime() == 14610)
		pPerson->ResetCost();


}
