	//
	//  output.cpp
	//  priorityQ
	//
	//  Created by Jack Olney on 28/10/2014.
	//  Copyright (c) 2014 Jack Olney. All rights reserved.
	//

#include <iostream>
#include "output.h"
#include "impact.h"
#include "cost.h"
#include "outputUpdate.h"

using namespace std;

double * theCARE;
double * theDALY;
double * theCOST;
double * thePOP;
double * theHIV;
double * theART;

/////////////////////
/////////////////////

void SeedOutput(person * const thePerson)
{
	double yr [60];
	for(size_t i=0;i<60;i++) {
		yr[i] = 365.25 + (i * 365.25);
		if(thePerson->GetBirthDay() < yr[i])
			new Output(thePerson,yr[i]);
	}
}

/////////////////////
/////////////////////

Output::Output(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Output::~Output()
{}

bool Output::CheckValid()
{
	return true;
}

void Output::Execute()
{
	if(GetTime() >= 14610) {
		WriteDaly(pPerson);
		WriteCost(pPerson);
	}
	WritePop(pPerson);
	WriteHiv(pPerson);
	WriteArt(pPerson);
}

/////////////////////
/////////////////////

void CreateOutputArray()
{
	theCARE = new double[5]; //NeverDiagnosed, DiagnosedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.
	theDALY = new double[20];
	theCOST = new double[20];
	thePOP = new double[60];
	theHIV = new double[60];
	theART = new double[60];
	
	for(size_t i=0;i<60;i++) {
		if(i<5)
			theCARE[i] = 0;
		if(i<20)
			theDALY[i] = 0;
		if(i<20)
			theCOST[i] = 0;
		thePOP[i] = 0;
		theHIV[i] = 0;
		theART[i] = 0;
	}
}

/////////////////////
/////////////////////

void WriteCare(person * const thePerson, const double theTime)
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
}

/////////////////////
/////////////////////
