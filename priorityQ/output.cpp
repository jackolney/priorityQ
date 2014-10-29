//
//  output.cpp
//  priorityQ
//
//  Created by Jack Olney on 28/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "output.h"

using namespace std;

double * theCARE;
double * theDALY;
double * theCOST;

/////////////////////
/////////////////////

void CreateCareExperienceArray()
{
	theCARE = new double[5]; //NeverDiagnosed, DiagnosedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.
	
	for(size_t i=0;i<5;i++)
		theCARE[i] = 0;
}

/////////////////////
/////////////////////

void CreateDalyArray()
{
	theDALY = new double[20];
	
	for(size_t i=0;i<20;i++)
		theDALY[i] = 0;
}

/////////////////////
/////////////////////

void CreateCostArray()
{
	theCOST = new double[20];
	
	for(size_t i=0;i<20;i++)
		theCOST[i] = 0;
}

/////////////////////
/////////////////////

void FillOutCareExperienceArray(person * const thePerson, const double theTime)
{
	if(thePerson->GetHivDeath() && theTime >= 14610 && theTime < 21915) {
			//NeverDiagnosed
		theCARE[0] += !thePerson->GetDiagnosedState();
			//DiagnosedButNeverInitiatedArt
		theCARE[1] += (thePerson->GetDiagnosedState() && !thePerson->GetEverArt());
			//ArtLate
		theCARE[2] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() == 1);
			//ArtButDiedOffArt
		theCARE[3] += (thePerson->GetEverArt() && !thePerson->GetArtDeath());
			//ArtEarly
		theCARE[4] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() > 1);
	}
	for(size_t i=0 ; i<5; i++)
		cout << theCARE[i] << endl;
}

/////////////////////
/////////////////////
