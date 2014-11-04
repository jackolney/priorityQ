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
	thePerson->SetLabCd4Test(labCd4TestCost);
}

/////////////////////
/////////////////////

void ChargePreArtClinicCd4ResultVisit(person * const thePerson)
{
	thePerson->SetPreArtClinicVisitCost(preArtClinicVisitCost);
}

/////////////////////
/////////////////////

void ChargePocCd4Test(person * const thePerson)
{
	thePerson->SetPocCd4Test(pocCd4TestCost);
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

void ChargeAdherence(person * const thePerson)
{
	if(adherenceFlag && thePerson->GetArtInitiationState()) {
		if(thePerson->GetArtDay() <= 14610)
			thePerson->SetAnnualAdherenceCost((((theQ->GetTime() - 14610) + thePerson->GetArtTime()) / 365.25) * annualAdherenceCost);
		else
			thePerson->SetAnnualAdherenceCost((((theQ->GetTime() - thePerson->GetArtDay()) + thePerson->GetArtTime()) / 365.25) * annualAdherenceCost);
	} else
		thePerson->SetAnnualAdherenceCost((thePerson->GetArtTime() / 365.25) * annualAdherenceCost);
}

/////////////////////
/////////////////////

void ChargeOutreach(person * const thePerson)
{
	thePerson->SetOutreachCost(outreachCost);
}

/////////////////////
/////////////////////

void WriteCost(person * const thePerson)
{
	if(thePerson->Alive()) {
		ChargeArtCare(thePerson);
		ChargeAdherence(thePerson);
		
		/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
		double yr [20];
		for(size_t i = 0; i<20; i++)
			yr[i] = 14975.25 + (i * 365.25);
		
		unsigned int i = 0;
		while(theQ->GetTime() > yr[i])
			i++;
		
	if(theQ->GetTime() > 14610)
		theCOST[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4Test() + thePerson->GetPocCd4Test() + thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetOutreachCost();
	
	if(theQ->GetTime() == 14610)
		thePerson->ResetCost();
	}
}

/////////////////////
/////////////////////
