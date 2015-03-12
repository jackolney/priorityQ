	//
	//  wp19.cpp
	//  priorityQ
	//
	//  Created by Jack Olney on 12/03/2015.
	//  Copyright (c) 2015 Jack Olney. All rights reserved.
	//

#include <iostream>
#include "wp19.h"
#include "impact.h"
#include "cost.h"
#include "wp19Update.h"

using namespace std;

int * theGuidelines_PopDist_HivNegative;
int * theGuidelines_PopDist_500_NeverDiag;
int * theGuidelines_PopDist_500_DiagNotInCare;
int * theGuidelines_PopDist_500_InCareNeverArt;
int * theGuidelines_PopDist_500_ArtLessSixMonths;
int * theGuidelines_PopDist_500_ArtMoreSixMonths;
int * theGuidelines_PopDist_500_OffArt;
int * theGuidelines_PopDist_350500_NeverDiag;
int * theGuidelines_PopDist_350500_DiagNotInCare;
int * theGuidelines_PopDist_350500_InCareNeverArt;
int * theGuidelines_PopDist_350500_ArtLessSixMonths;
int * theGuidelines_PopDist_350500_ArtMoreSixMonths;
int * theGuidelines_PopDist_350500_OffArt;
int * theGuidelines_PopDist_200350_NeverDiag;
int * theGuidelines_PopDist_200350_DiagNotInCare;
int * theGuidelines_PopDist_200350_InCareNeverArt;
int * theGuidelines_PopDist_200350_ArtLessSixMonths;
int * theGuidelines_PopDist_200350_ArtMoreSixMonths;
int * theGuidelines_PopDist_200350_OffArt;
int * theGuidelines_PopDist_200_NeverDiag;
int * theGuidelines_PopDist_200_DiagNotInCare;
int * theGuidelines_PopDist_200_InCareNeverArt;
int * theGuidelines_PopDist_200_ArtLessSixMonths;
int * theGuidelines_PopDist_200_ArtMoreSixMonths;
int * theGuidelines_PopDist_200_OffArt;
int * theGuidelines_Death_HivNegative;
int * theGuidelines_Death_500_NeverDiag;
int * theGuidelines_Death_500_DiagNotInCare;
int * theGuidelines_Death_500_InCareNeverArt;
int * theGuidelines_Death_500_ArtLessSixMonths;
int * theGuidelines_Death_500_ArtMoreSixMonths;
int * theGuidelines_Death_500_OffArt;
int * theGuidelines_Death_350500_NeverDiag;
int * theGuidelines_Death_350500_DiagNotInCare;
int * theGuidelines_Death_350500_InCareNeverArt;
int * theGuidelines_Death_350500_ArtLessSixMonths;
int * theGuidelines_Death_350500_ArtMoreSixMonths;
int * theGuidelines_Death_350500_OffArt;
int * theGuidelines_Death_200350_NeverDiag;
int * theGuidelines_Death_200350_DiagNotInCare;
int * theGuidelines_Death_200350_InCareNeverArt;
int * theGuidelines_Death_200350_ArtLessSixMonths;
int * theGuidelines_Death_200350_ArtMoreSixMonths;
int * theGuidelines_Death_200350_OffArt;
int * theGuidelines_Death_200_NeverDiag;
int * theGuidelines_Death_200_DiagNotInCare;
int * theGuidelines_Death_200_InCareNeverArt;
int * theGuidelines_Death_200_ArtLessSixMonths;
int * theGuidelines_Death_200_ArtMoreSixMonths;
int * theGuidelines_Death_200_OffArt;
int * theGuidelines_Art_500;
int * theGuidelines_Art_350500;
int * theGuidelines_Art_200350;
int * theGuidelines_Art_200;
int * theGuidelines_NewInfectionsAdult;
int * theGuidelines_NewDiagnoses;
int * theGuidelines_PreArtDropout;
int * theGuidelines_ArtDropout;

	/////////////////////
	/////////////////////

void SeedGuidelinesOutput(person * const thePerson)
{
	double yr [36];
	for(size_t i=0; i<36; i++) {
		yr[i] = 11140.12 + (i * 365.25);
		if(thePerson->GetBirthDay() < yr[i])
			new GuidelinesOutput(thePerson,yr[i],i);
	}
}

	/////////////////////
	/////////////////////

GuidelinesOutput::GuidelinesOutput(person * const thePerson, const double Time, const int theIndex) :
event(Time),
pPerson(thePerson),
index(theIndex)
{}

GuidelinesOutput::~GuidelinesOutput()
{}

bool GuidelinesOutput::CheckValid()
{
	return pPerson->Alive();
}

void GuidelinesOutput::Execute()
{
	WriteGuidelinesPopDist(pPerson,index);
}

	/////////////////////
	/////////////////////

void CreateGuidelinesArray()
{
	theGuidelines_PopDist_HivNegative = new int[36];
	theGuidelines_PopDist_500_NeverDiag = new int[36];
	theGuidelines_PopDist_500_DiagNotInCare = new int[36];
	theGuidelines_PopDist_500_InCareNeverArt = new int[36];
	theGuidelines_PopDist_500_ArtLessSixMonths = new int[36];
	theGuidelines_PopDist_500_ArtMoreSixMonths = new int[36];
	theGuidelines_PopDist_500_OffArt = new int[36];
	theGuidelines_PopDist_350500_NeverDiag = new int[36];
	theGuidelines_PopDist_350500_DiagNotInCare = new int[36];
	theGuidelines_PopDist_350500_InCareNeverArt = new int[36];
	theGuidelines_PopDist_350500_ArtLessSixMonths = new int[36];
	theGuidelines_PopDist_350500_ArtMoreSixMonths = new int[36];
	theGuidelines_PopDist_350500_OffArt = new int[36];
	theGuidelines_PopDist_200350_NeverDiag = new int[36];
	theGuidelines_PopDist_200350_DiagNotInCare = new int[36];
	theGuidelines_PopDist_200350_InCareNeverArt = new int[36];
	theGuidelines_PopDist_200350_ArtLessSixMonths = new int[36];
	theGuidelines_PopDist_200350_ArtMoreSixMonths = new int[36];
	theGuidelines_PopDist_200350_OffArt = new int[36];
	theGuidelines_PopDist_200_NeverDiag = new int[36];
	theGuidelines_PopDist_200_DiagNotInCare = new int[36];
	theGuidelines_PopDist_200_InCareNeverArt = new int[36];
	theGuidelines_PopDist_200_ArtLessSixMonths = new int[36];
	theGuidelines_PopDist_200_ArtMoreSixMonths = new int[36];
	theGuidelines_PopDist_200_OffArt = new int[36];
	theGuidelines_Death_HivNegative = new int[36];
	theGuidelines_Death_500_NeverDiag = new int[36];
	theGuidelines_Death_500_DiagNotInCare = new int[36];
	theGuidelines_Death_500_InCareNeverArt = new int[36];
	theGuidelines_Death_500_ArtLessSixMonths = new int[36];
	theGuidelines_Death_500_ArtMoreSixMonths = new int[36];
	theGuidelines_Death_500_OffArt = new int[36];
	theGuidelines_Death_350500_NeverDiag = new int[36];
	theGuidelines_Death_350500_DiagNotInCare = new int[36];
	theGuidelines_Death_350500_InCareNeverArt = new int[36];
	theGuidelines_Death_350500_ArtLessSixMonths = new int[36];
	theGuidelines_Death_350500_ArtMoreSixMonths = new int[36];
	theGuidelines_Death_350500_OffArt = new int[36];
	theGuidelines_Death_200350_NeverDiag = new int[36];
	theGuidelines_Death_200350_DiagNotInCare = new int[36];
	theGuidelines_Death_200350_InCareNeverArt = new int[36];
	theGuidelines_Death_200350_ArtLessSixMonths = new int[36];
	theGuidelines_Death_200350_ArtMoreSixMonths = new int[36];
	theGuidelines_Death_200350_OffArt = new int[36];
	theGuidelines_Death_200_NeverDiag = new int[36];
	theGuidelines_Death_200_DiagNotInCare = new int[36];
	theGuidelines_Death_200_InCareNeverArt = new int[36];
	theGuidelines_Death_200_ArtLessSixMonths = new int[36];
	theGuidelines_Death_200_ArtMoreSixMonths = new int[36];
	theGuidelines_Death_200_OffArt = new int[36];
	theGuidelines_Art_500 = new int[36];
	theGuidelines_Art_350500 = new int[36];
	theGuidelines_Art_200350 = new int[36];
	theGuidelines_Art_200 = new int[36];
	theGuidelines_NewInfectionsAdult = new int[36];
	theGuidelines_NewDiagnoses = new int[36];
	theGuidelines_PreArtDropout = new int[36];
	theGuidelines_ArtDropout = new int[36];
	
	for(size_t i=0;i<36;i++) {
		theGuidelines_PopDist_HivNegative[i] = 0;
		theGuidelines_PopDist_500_NeverDiag[i] = 0;
		theGuidelines_PopDist_500_DiagNotInCare[i] = 0;
		theGuidelines_PopDist_500_InCareNeverArt[i] = 0;
		theGuidelines_PopDist_500_ArtLessSixMonths[i] = 0;
		theGuidelines_PopDist_500_ArtMoreSixMonths[i] = 0;
		theGuidelines_PopDist_500_OffArt[i] = 0;
		theGuidelines_PopDist_350500_NeverDiag[i] = 0;
		theGuidelines_PopDist_350500_DiagNotInCare[i] = 0;
		theGuidelines_PopDist_350500_InCareNeverArt[i] = 0;
		theGuidelines_PopDist_350500_ArtLessSixMonths[i] = 0;
		theGuidelines_PopDist_350500_ArtMoreSixMonths[i] = 0;
		theGuidelines_PopDist_350500_OffArt[i] = 0;
		theGuidelines_PopDist_200350_NeverDiag[i] = 0;
		theGuidelines_PopDist_200350_DiagNotInCare[i] = 0;
		theGuidelines_PopDist_200350_InCareNeverArt[i] = 0;
		theGuidelines_PopDist_200350_ArtLessSixMonths[i] = 0;
		theGuidelines_PopDist_200350_ArtMoreSixMonths[i] = 0;
		theGuidelines_PopDist_200350_OffArt[i] = 0;
		theGuidelines_PopDist_200_NeverDiag[i] = 0;
		theGuidelines_PopDist_200_DiagNotInCare[i] = 0;
		theGuidelines_PopDist_200_InCareNeverArt[i] = 0;
		theGuidelines_PopDist_200_ArtLessSixMonths[i] = 0;
		theGuidelines_PopDist_200_ArtMoreSixMonths[i] = 0;
		theGuidelines_PopDist_200_OffArt[i] = 0;
		theGuidelines_Death_HivNegative[i] = 0;
		theGuidelines_Death_500_NeverDiag[i] = 0;
		theGuidelines_Death_500_DiagNotInCare[i] = 0;
		theGuidelines_Death_500_InCareNeverArt[i] = 0;
		theGuidelines_Death_500_ArtLessSixMonths[i] = 0;
		theGuidelines_Death_500_ArtMoreSixMonths[i] = 0;
		theGuidelines_Death_500_OffArt[i] = 0;
		theGuidelines_Death_350500_NeverDiag[i] = 0;
		theGuidelines_Death_350500_DiagNotInCare[i] = 0;
		theGuidelines_Death_350500_InCareNeverArt[i] = 0;
		theGuidelines_Death_350500_ArtLessSixMonths[i] = 0;
		theGuidelines_Death_350500_ArtMoreSixMonths[i] = 0;
		theGuidelines_Death_350500_OffArt[i] = 0;
		theGuidelines_Death_200350_NeverDiag[i] = 0;
		theGuidelines_Death_200350_DiagNotInCare[i] = 0;
		theGuidelines_Death_200350_InCareNeverArt[i] = 0;
		theGuidelines_Death_200350_ArtLessSixMonths[i] = 0;
		theGuidelines_Death_200350_ArtMoreSixMonths[i] = 0;
		theGuidelines_Death_200350_OffArt[i] = 0;
		theGuidelines_Death_200_NeverDiag[i] = 0;
		theGuidelines_Death_200_DiagNotInCare[i] = 0;
		theGuidelines_Death_200_InCareNeverArt[i] = 0;
		theGuidelines_Death_200_ArtLessSixMonths[i] = 0;
		theGuidelines_Death_200_ArtMoreSixMonths[i] = 0;
		theGuidelines_Death_200_OffArt[i] = 0;
		theGuidelines_Art_500[i] = 0;
		theGuidelines_Art_350500[i] = 0;
		theGuidelines_Art_200350[i] = 0;
		theGuidelines_Art_200[i] = 0;
		theGuidelines_NewInfectionsAdult[i] = 0;
		theGuidelines_NewDiagnoses[i] = 0;
		theGuidelines_PreArtDropout[i] = 0;
		theGuidelines_ArtDropout[i] = 0;
	}
}

	/////////////////////
	/////////////////////
