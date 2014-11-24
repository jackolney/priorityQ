//
//  outputUpdate.cpp
//  priorityQ
//
//  Created by Jack Olney on 30/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "outputUpdate.h"
#include "eventQ.h"

using namespace std;

extern eventQ * theQ;

extern double * theCARE;
extern double * thePOP;
extern double * theHIV;
extern double * thePOP_15to49;
extern double * theHIV_15to49;
extern double * theART_15to49;
extern double * thePOP_15plus;
extern double * theAidsDeath_15plus;
extern double * thePOP_AgeSex_2007;
extern double * theHIV_AgeSex_2007;
extern double * thePOP_NoArtCd4_2007;
extern double * thePOP_AgeSex_2012;
extern double * theHIV_AgeSex_2012;
extern double * thePOP_AgeSex_2014;
extern double * theHIV_AgeSex_2014;
extern double * theCD4_200;
extern double * theCD4_200350;
extern double * theCD4_350500;
extern double * theCD4_500;
extern double * theCD4_200_Art;
extern double * theCD4_200350_Art;
extern double * theCD4_350500_Art;
extern double * theCD4_500_Art;
extern double * theWHO_1;
extern double * theWHO_2;
extern double * theWHO_3;
extern double * theWHO_4;
extern double * theWHO_1_Art;
extern double * theWHO_2_Art;
extern double * theWHO_3_Art;
extern double * theWHO_4_Art;

/////////////////////
/////////////////////

void WritePop(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 59)
		i++;
	
	if(theQ->GetTime() > thePerson->GetBirthDay()) {
		thePOP[i] += thePerson->Alive();
		if(thePerson->GetAge() > 15 * 365.25)
			thePOP_15plus[i] += thePerson->Alive();
		if(thePerson->GetAge() > 15 * 365.25 && thePerson->GetAge() <= 49 * 365.25)
			thePOP_15to49[i] += thePerson->Alive();
	}
}

/////////////////////
/////////////////////

void WriteHiv(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 59)
		i++;
	
	if(thePerson->Alive()) {
		theHIV[i] += thePerson->GetSeroStatus();
		if(thePerson->GetAge() > 15 * 365.25 && thePerson->GetAge() <= 49 * 365.25)
			theHIV_15to49[i] += thePerson->GetSeroStatus();
	}
}

/////////////////////
/////////////////////

void WriteArt(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 59)
		i++;
	
	if(thePerson->Alive()) {
		if(thePerson->GetAge() > 15 * 365.25 && thePerson->GetAge() <= 49 * 365.25)
			theART_15to49[i] += thePerson->GetArtInitiationState();
	}
}

/////////////////////
/////////////////////

void WriteCare(person * const thePerson, const double theTime)
{
	if(thePerson->GetHivDeath() && theTime >= 14610 && theTime < 21915) {
			// NeverDiagnosed
		theCARE[0] += !thePerson->GetDiagnosedState();
			// DiagnosedButNeverInitiatedArt
		theCARE[1] += (thePerson->GetDiagnosedState() && !thePerson->GetEverArt());
			// ArtLate
		theCARE[2] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() == 1);
			// ArtButDiedOffArt
		theCARE[3] += (thePerson->GetEverArt() && !thePerson->GetArtDeath());
			// ArtEarly
		theCARE[4] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() > 1);
	}
}

/////////////////////
/////////////////////

void WriteAidsDeath(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 59)
		i++;
	
	if(thePerson->GetAge() > 15 * 365.25)
		theAidsDeath_15plus[i] += thePerson->GetSeroStatus();
}

/////////////////////
/////////////////////

void Write2007(person * const thePerson)
{
	if(theQ->GetTime() > thePerson->GetBirthDay()) {
		if(thePerson->GetAge() > 15 * 365.25 && thePerson->GetAge() <= 64 * 365.25) {
			const unsigned int ageCatMax [10] = {19,24,29,34,39,44,49,54,59,64};
			unsigned int i = 0;
			while(thePerson->GetAge() / 365.25 > ageCatMax[i] && i < 9)
				i++;
			
			if(thePerson->GetGender())
				i += 10;
			
			thePOP_AgeSex_2007[i] += thePerson->Alive();
			if(thePerson->Alive()) {
				theHIV_AgeSex_2007[i] += thePerson->GetSeroStatus();
				if(!thePerson->GetArtInitiationState()) {
					if(thePerson->GetCurrentCd4() == 1)
						thePOP_NoArtCd4_2007[0]++;
					else if(thePerson->GetCurrentCd4() == 2)
						thePOP_NoArtCd4_2007[1]++;
					else if(thePerson->GetCurrentCd4() == 3)
						thePOP_NoArtCd4_2007[2]++;
					else if(thePerson->GetCurrentCd4() == 4)
						thePOP_NoArtCd4_2007[3]++;
				}
			}
		}
	}
}

/////////////////////
/////////////////////

void Write2012(person * const thePerson)
{
	if(theQ->GetTime() > thePerson->GetBirthDay()) {
		if(thePerson->GetAge() > 15 * 365.25 && thePerson->GetAge() <= 64 * 365.25) {
			const unsigned int ageCatMax [8] = {19,24,29,34,39,44,49,64};
			unsigned int i = 0;
			while(thePerson->GetAge() / 365.25 > ageCatMax[i] && i < 7)
				i++;
			
			if(thePerson->GetGender())
				i += 8;
			
			thePOP_AgeSex_2012[i] += thePerson->Alive();
			if(thePerson->Alive())
				theHIV_AgeSex_2012[i] += thePerson->GetSeroStatus();
		}
	}
}

/////////////////////
/////////////////////

void Write2014(person * const thePerson)
{
	if(theQ->GetTime() > thePerson->GetBirthDay()) {		
		const unsigned int ageCatMax [5] = {14,21,29,46,200};
		unsigned int i = 0;
		while(thePerson->GetAge() / 365.25 > ageCatMax[i] && i < 4)
			i++;
		
		if(thePerson->GetGender())
			i += 5;
		
		thePOP_AgeSex_2014[i] += thePerson->Alive();
		if(thePerson->Alive())
			theHIV_AgeSex_2014[i] += thePerson->GetSeroStatus();
	}
}

/////////////////////
/////////////////////

void WriteCd4(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 59)
		i++;

	if(theQ->GetTime() > thePerson->GetBirthDay()) {
		if(thePerson->GetCurrentCd4() == 1)
			theCD4_200[i] += thePerson->Alive();
		else if(thePerson->GetCurrentCd4() == 2)
			theCD4_200350[i] += thePerson->Alive();
		else if(thePerson->GetCurrentCd4() == 3)
			theCD4_350500[i] += thePerson->Alive();
		else if(thePerson->GetCurrentCd4() == 4)
			theCD4_500[i] += thePerson->Alive();
	}
	
	
	if(theQ->GetTime() > thePerson->GetBirthDay() && thePerson->Alive()) {
		if(thePerson->GetCurrentCd4() == 1)
			theCD4_200_Art[i] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentCd4() == 2)
			theCD4_200350_Art[i] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentCd4() == 3)
			theCD4_350500_Art[i] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentCd4() == 4)
			theCD4_500_Art[i] += thePerson->GetArtInitiationState();
	}
}

/////////////////////
/////////////////////

void WriteWho(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 59)
		i++;
	
	if(theQ->GetTime() > thePerson->GetBirthDay()) {
		if(thePerson->GetCurrentWho() == 1)
			theWHO_1[i] += thePerson->Alive();
		else if(thePerson->GetCurrentWho() == 2)
			theWHO_2[i] += thePerson->Alive();
		else if(thePerson->GetCurrentWho() == 3)
			theWHO_3[i] += thePerson->Alive();
		else if(thePerson->GetCurrentWho() == 4)
			theWHO_4[i] += thePerson->Alive();
	}
	
	if(theQ->GetTime() > thePerson->GetBirthDay() && thePerson->Alive()) {
		if(thePerson->GetCurrentWho() == 1)
			theWHO_1_Art[i] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentWho() == 2)
			theWHO_2_Art[i] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentWho() == 3)
			theWHO_3_Art[i] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentWho() == 4)
			theWHO_4_Art[i] += thePerson->GetArtInitiationState();
	}
}

/////////////////////
/////////////////////
