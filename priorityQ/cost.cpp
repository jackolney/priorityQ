//
//  cost.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "cost.h"
#include "person.h"
#include "toolbox.h"

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
	thePerson->SetLabCd4Test(labCd4Test);
}

/////////////////////
/////////////////////

void ChargePreArtClinicResultVisit(person * const thePerson)
{
	thePerson->SetPreArtClinicVisitCost(preArtClinicVisitCost);
}

/////////////////////
/////////////////////

void ChargeArtCare(person * const thePerson)
{
		//This is an annual thing so not sure how to calculate it.
		//Have an annual cost function blasting the value calculated by Time since an Art initiation day.
}

/////////////////////
/////////////////////

/* COST */
//double iHctVisitCost;
//double iRapidHivTestCost;
//double iPreArtClinicVisitCost;
//double iLabCd4Test;
//double iPocCd4Test;
//double iAnnualArtCost;


//const double hctVisitCost = 8.00;
//const double rapidHivTestCost = 10.00;
//const double preArtClinicVisitCost = 28.00;
//const double labCd4Test = 12.00;
//const double pocCd4Test = 42.00;
//const double annualArtCost = 367.00;
//
//	//How to use:
///* HBCT */
//	//HCT visit + HIV-test = 8 + 10 = $18
//	//HCT visit + HIV-test + POC-CD4 test = 8 + 10 + 42 = $60
//
///* VCT or PICT */
//	//Clinic visit + HIV-test + lab-CD4 test = 28 + 10 + 12 = $50 (Test visit)
//	//Clinic visit = $28 (Result visit)
//	//Clinic visit + HIV-test + POC-CD4 test = 28 + 10 + 42 = $80
//
///* Pre-ART Care */
//	//Clinic visit + lab-CD4 test = 28 + 12 = $40 (Test visit)
//	//Clinic visit = $28 (Result visit)
//	//Clinic visit + POC-CD4 test = 28 + 42 = $70