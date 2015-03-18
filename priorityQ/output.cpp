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
double * thePOP_15to49;
double * theHIV_15to49;
double * theART_15to49;
double * thePOP_15plus;
double * theAidsDeath_15plus;
double * thePOP_AgeSex_2007;
double * theHIV_AgeSex_2007;
double * thePOP_NoArtCd4_2007;
double * thePOP_AgeSex_2012;
double * theHIV_AgeSex_2012;
double * thePOP_AgeSex_2014;
double * theHIV_AgeSex_2014;
double * theCD4_200;
double * theCD4_200350;
double * theCD4_350500;
double * theCD4_500;
double * theCD4_200_Art;
double * theCD4_200350_Art;
double * theCD4_350500_Art;
double * theCD4_500_Art;
double * theWHO_1;
double * theWHO_2;
double * theWHO_3;
double * theWHO_4;
double * theWHO_1_Art;
double * theWHO_2_Art;
double * theWHO_3_Art;
double * theWHO_4_Art;
double * theINCIDENCE;
double * thePreArtCOST;
double * theArtCOST;
double * thePreArtCOST_Hiv;
double * theArtCOST_Hiv;
double * theCLINIC;
double * theDeath;
double * theAidsDeath;
double * theDeath_2010_Age;
double * theAidsDeath_2010_Age;

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
	WriteCd4(pPerson);
	WriteWho(pPerson);
	if(GetTime() == 13879.5)
		Write2007(pPerson);
	if(GetTime() == 15705.75)
		Write2012(pPerson);
	if(GetTime() == 16436.25)
		Write2014(pPerson);
}

/////////////////////
/////////////////////

void CreateOutputArray()
{
	theCARE = new double[6]; // NeverDiagnosed, DiagnosedButNeverLinkedToCare, DiagnosedLinkedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.
	theDALY = new double[20];
	theCOST = new double[20];
	thePOP = new double[60];
	theHIV = new double[60];
	thePOP_15to49 = new double[60];
	theHIV_15to49 = new double[60];
	theART_15to49 = new double[60];
	thePOP_15plus = new double[60];
	theAidsDeath_15plus = new double[60];
	thePOP_AgeSex_2007 = new double[20];
	theHIV_AgeSex_2007 = new double[20];
	thePOP_NoArtCd4_2007 = new double[4];
	thePOP_AgeSex_2012 = new double[16];
	theHIV_AgeSex_2012 = new double[16];
	thePOP_AgeSex_2014 = new double[10];
	theHIV_AgeSex_2014 = new double[10];
	theCD4_200 = new double[60];
	theCD4_200350 = new double[60];
	theCD4_350500 = new double[60];
	theCD4_500 = new double[60];
	theCD4_200_Art = new double[60];
	theCD4_200350_Art = new double[60];
	theCD4_350500_Art = new double[60];
	theCD4_500_Art = new double[60];
	theWHO_1 = new double[60];
	theWHO_2 = new double[60];
	theWHO_3 = new double[60];
	theWHO_4 = new double[60];
	theWHO_1_Art = new double[60];
	theWHO_2_Art = new double[60];
	theWHO_3_Art = new double[60];
	theWHO_4_Art = new double[60];
	theINCIDENCE = new double[60];
	thePreArtCOST = new double[20];
	theArtCOST = new double[20];
	thePreArtCOST_Hiv = new double[20];
	theArtCOST_Hiv = new double[20];
	theCLINIC = new double[5]; // NeverDiagnosed, DiagnosedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.
	theDeath = new double[60];
	theAidsDeath = new double[60];
	theDeath_2010_Age = new double[20];
	theAidsDeath_2010_Age = new double[20];
	
	for(size_t i=0;i<60;i++) {
		if(i<4)
			thePOP_NoArtCd4_2007[i] = 0;
		if(i<5)
			theCLINIC[i] = 0;
		if(i<6)
			theCARE[i] = 0;
		if(i<10) {
			thePOP_AgeSex_2014[i] = 0;
			theHIV_AgeSex_2014[i] = 0;
		}
		if(i<20) {
			theDALY[i] = 0;
			theCOST[i] = 0;
			thePOP_AgeSex_2007[i] = 0;
			theHIV_AgeSex_2007[i] = 0;
			thePreArtCOST[i] = 0;
			theArtCOST[i] = 0;
			thePreArtCOST_Hiv[i] = 0;
			theArtCOST_Hiv[i] = 0;
			theDeath_2010_Age[i] = 0;
			theAidsDeath_2010_Age[i] = 0;
		}
		if(i<16) {
			thePOP_AgeSex_2012[i] = 0;
			theHIV_AgeSex_2012[i] = 0;
		}
		thePOP[i] = 0;
		theHIV[i] = 0;
		thePOP_15to49[i] = 0;
		theHIV_15to49[i] = 0;
		theART_15to49[i] = 0;
		thePOP_15plus[i] = 0;
		theAidsDeath_15plus[i] = 0;
		theCD4_200[i] = 0;
		theCD4_200350[i] = 0;
		theCD4_350500[i] = 0;
		theCD4_500[i] = 0;
		theCD4_200_Art[i] = 0;
		theCD4_200350_Art[i] = 0;
		theCD4_350500_Art[i] = 0;
		theCD4_500_Art[i] = 0;
		theWHO_1[i] = 0;
		theWHO_2[i] = 0;
		theWHO_3[i] = 0;
		theWHO_4[i] = 0;
		theWHO_1_Art[i] = 0;
		theWHO_2_Art[i] = 0;
		theWHO_3_Art[i] = 0;
		theWHO_4_Art[i] = 0;
		theINCIDENCE[i] = 0;
		theDeath[i] = 0;
		theAidsDeath[i] = 0;
	}
}

/////////////////////
/////////////////////
