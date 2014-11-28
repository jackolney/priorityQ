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
extern double * thePreArtCOST;
extern double * theArtCOST;
extern double * thePreArtCOST_Hiv;
extern double * theArtCOST_Hiv;

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
	thePerson->SetLabCd4TestCost(labCd4TestCost);
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
	thePerson->SetPocCd4TestCost(pocCd4TestCost);
}

/////////////////////
/////////////////////

void ChargeArtCare(person * const thePerson)
{
	if(thePerson->GetArtInitiationState()) {
		double yr [22];
		for(size_t i = 0; i<22; i++)
			yr[i] = 14610 + (i * 365.25);
		
		unsigned int i = 0;
		while(theQ->GetTime() > yr[i] && i < 21)
			i++;
		
		if(thePerson->GetArtDay() <= yr[i-1])
			thePerson->SetAnnualArtCost((((theQ->GetTime() - yr[i-1]) + thePerson->GetArtTime()) / 365.25) * annualArtCost);
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
		double yr [22];
		for(size_t i = 0; i<22; i++)
			yr[i] = 14610 + (i * 365.25);
		
		unsigned int i = 0;
		while(theQ->GetTime() > yr[i] && i < 21)
			i++;
		
		if(thePerson->GetArtDay() <= yr[i-1])
			thePerson->SetAnnualAdherenceCost((((theQ->GetTime() - yr[i-1]) + thePerson->GetArtTime()) / 365.25) * annualAdherenceCost);
		else
			thePerson->SetAnnualAdherenceCost((((theQ->GetTime() - thePerson->GetArtDay()) + thePerson->GetArtTime()) / 365.25) * annualAdherenceCost);
	} else
		thePerson->SetAnnualAdherenceCost((thePerson->GetArtTime() / 365.25) * annualAdherenceCost);
}

/////////////////////
/////////////////////

void ChargePreArtOutreach(person * const thePerson)
{
	thePerson->SetPreArtOutreachCost(outreachCost);
}

/////////////////////
/////////////////////

void ChargeArtOutreach(person * const thePerson)
{
	thePerson->SetArtOutreachCost(outreachCost);
}

/////////////////////
/////////////////////

void WriteCost(person * const thePerson)
{
	if(thePerson->Alive()) {
		
		/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
		double yr [20];
		for(size_t i = 0; i<20; i++)
			yr[i] = 14975.25 + (i * 365.25);
		
		unsigned int i = 0;
		while(theQ->GetTime() > yr[i])
			i++;
		
		if(theQ->GetTime() > 14610) {
			ChargeArtCare(thePerson);
			ChargeAdherence(thePerson);
			theCOST[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4TestCost() + thePerson->GetPocCd4TestCost() + thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetArtOutreachCost() + thePerson->GetPreArtOutreachCost();
			
			thePreArtCOST[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4TestCost() + thePerson->GetPocCd4TestCost() + thePerson->GetPreArtOutreachCost();
			
			theArtCOST[i] += thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetArtOutreachCost() + thePerson->GetPreArtOutreachCost();

			if(thePerson->GetSeroStatus()) {
				thePreArtCOST_Hiv[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4TestCost() + thePerson->GetPocCd4TestCost() + thePerson->GetPreArtOutreachCost();
				
				theArtCOST_Hiv[i] += thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetArtOutreachCost() + thePerson->GetPreArtOutreachCost();
			}
			
		}
	
		thePerson->ResetCost();
	}
}

/////////////////////
/////////////////////
