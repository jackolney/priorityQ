//
//  population.cpp
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "rng.h"
#include "population.h"
#include "cohort.h"
#include "output.h"
#include "update.h"
#include "eventQ.h"
#include "events.h"
#include "toolbox.h"

using namespace std;

extern eventQ * theQ;
extern Rng * theRng;

population::population(const double theSize) :
sizeAdjustment(theSize),
populationSize(0),
incidentCases(0),
referenceYear(11688),
beta(0)
{
	Generate();
	InitialiseVector();
	CreateOutputArray();
	ScheduleIncidence(this);
	ScheduleBetaCalculation(this);
	for(size_t i=0;i<5;i++)
		infectiousness[i] = 0;
}

population::~population()
{}

/////////////
// METHODS //
/////////////

void population::Generate()
{	
		/* Function to schedule cohorts over time (not being used until I scale everything up) */
	const double popSize [60] = {11252466,11657477,12083159,12529800,12997438,13486241,13995996,14527242,15081677,15661480,16267906,16901167,17559844,18241424,18942464,19660018,20392312,21138372,21896890,22666720,23446439,24237056,25036941,25839132,26634659,27418077,28186224,28943647,29702246,30478597,31285050,32126351,33000524,33905011,34834606,35785718,36757498,37752304,38773277,39824734,40909194,42027891,43178141,44359872,45573945,46821246,48102684,49419194,50771734,52161292,53588880,55055540,56562340,58110380,59700787,61334722,63013375,64737971,66509767,68330055};

	for(int i = 0; i < 60; i++) {
		new cohort(this,popSize[i] / sizeAdjustment,i * 365.25);
		cout << popSize[i] / sizeAdjustment << endl;
	}

	
		//TEMPORARY TESTING PLATFORM//
//	double yr = 0; //specifiees startTime for individuals.
//	int cohortArray [1] = {1};
//	
//	for(int i = 0; i < 1; i++) {
//		new cohort(this,cohortArray[i],yr);
//		yr += 365;
//	}
}

////////////////////
// VECTOR METHODS //
////////////////////

void population::InitialiseVector()
{
		// Rows 0 to 33 are Susceptible. Rows 34 to 67 are Infected.
	people.resize(68,vector<person *>(0));
}

void population::AddPerson(person * thePerson)
{
	PushInVector(thePerson);
	populationSize++;
}

void population::RemovePerson(person * thePerson)
{
	SwapOutVector(thePerson);
	SwapOutArray(thePerson);
	populationSize--;
}

void population::UpdateVector(person * thePerson)
{
	SwapOutVector(thePerson);
	PushInVector(thePerson);
}

/////////////////////
/////////////////////

void population::PushInVector(person * thePerson)
{
	// 0to4,5to9,10to14,15to19,20to24,25to29,30to34,35to39,40to44,45to49,50to54,55to59,60to64,64to69,70to74,75to79,>80
	unsigned int ageCatMax[17] = {4,9,14,19,24,29,34,39,44,49,54,59,64,69,74,79,200};
	unsigned int i = 0;
	const double theAge = thePerson->GetAge() / 365.25;
	
	while(theAge > ageCatMax[i] && i < 17)
		i++;
	
	if(i < 16)
		ScheduleVectorUpdate(thePerson,(ageCatMax[i] - theAge) * 365.25);
	
	if(thePerson->GetGender()) // If Male then i += 17;
		i += 17;
	
	if(thePerson->GetSeroStatus()) // If HIV-positive then i += 34;
		i += 34;
	
	thePerson->SetPersonIndex(people.at(i).size());
	thePerson->SetRowIndex(i);
	people.at(i).push_back(thePerson);

}

/////////////////////
/////////////////////

void population::SwapOutVector(person * thePerson)
{
	people.at(thePerson->GetRowIndex()).back()->SetRowIndex(thePerson->GetRowIndex());
	people.at(thePerson->GetRowIndex()).back()->SetPersonIndex(thePerson->GetPersonIndex());
	people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex()) = people.at(thePerson->GetRowIndex()).back();
	people.at(thePerson->GetRowIndex()).pop_back();
}

////////////////////////////
// INFECTIOUSNESS METHODS //
////////////////////////////

void population::UpdateArray(person * const thePerson)
{
	SwapOutArray(thePerson);
	PushInArray(thePerson);
}

void population::PushInArray(person * const thePerson)
{
	if(thePerson->Alive() && thePerson->GetSeroStatus()) {
		size_t index = 0;
		if(thePerson->GetArtInitiationState())
			index = 0;
		else switch(thePerson->GetCurrentCd4()) {
			case 1: index = 1; break;
			case 2: index = 2; break;
			case 3: index = 3; break;
			case 4: index = 4; break;
		}
		infectiousness[index]++;
		thePerson->SetInfectiousnessIndex(index);
	}
}

void population::SwapOutArray(person * const thePerson)
{
	if(thePerson->GetInfectiousnessIndex() != -1)
		infectiousness[thePerson->GetInfectiousnessIndex()]--;
}

///////////////////////////
// INCIDENCE CALCULATION //
///////////////////////////

double population::GetWeightedTotal() const
{
	/* Infectiousness weights */
	double wArt = 0.1;
	double w500 = 1.35;
	double w350500 = 1;
	double w200350 = 1.64;
	double w200 = 5.17;
	
	/* Calculate individual weights */
	double tArt = wArt * infectiousness[0];
	double t200 = w200 * infectiousness[1];
	double t200350 = w200350 * infectiousness[2];
	double t350500 = w350500 * infectiousness[3];
	double t500 = w500 * infectiousness[4];
	
	return(tArt + t500 + t350500 + t200350 + t200);
}

/////////////////////
/////////////////////

void population::CalculateBeta()
{
	D(cout << "Beta calculation..." << endl);
	beta = incidentCases / GetWeightedTotal();
	
	cout << "Time is = " << theQ->GetTime() << endl;
	cout << "InfectedCases (Array) = " << infectiousness[0] + infectiousness[1] + infectiousness[2] + infectiousness[3] + infectiousness[4] << endl;
	cout << "IncidentCases = " << incidentCases << endl;
	cout << "Weighted total = " << GetWeightedTotal() << endl;
	cout << "Beta is = " << beta << endl;
}

/////////////////////
/////////////////////

void population::CalculateIncidence()
{
	/* IncidenceCases (M+F Total - Spectrum2014) & IRR (0 to 16 are Female, 17 to 33 are Male */
	const double SpectrumIncidence[32] = {0,0,0,0,0,0,0,0,0,140,355,1134,1791,3418,6444,11887,21704,38623,66784,108993,165074,226131,269547,275327,243681,195612,152571,121318,101327,99767,93594,90036};
	const double IRR[34] = {0.000000,0.000000,0.000000,0.431475,0.979206,1.000000,0.848891,0.684447,0.550791,0.440263,0.336719,0.239474,0.167890,0.146594,0.171352,0.000000,0.000000,0.000000,0.000000,0.000000,0.244859,0.790423,1.000000,0.989385,0.854318,0.670484,0.493512,0.358977,0.282399,0.259244,0.264922,0.254788,0.164143,0.000000};

	/* Create incidence array (contains age and sex) */
	double incidence[34];
	for(size_t j=0;j<34;j++) {
		incidence[j] = 0;
	}
	
	/* Find total number of infected (I) */
	double I = 0;
	
	if(theQ->GetTime() < 32 * 365.25) {
	
		double yr [32];
		for(size_t i = 0; i<32; i++)
			yr[i] = 365.25 + (i * 365.25);
		
		unsigned int j = 0;
		while(theQ->GetTime() > yr[j] && j < 32)
			j++;
		
		I = SpectrumIncidence[j] / sizeAdjustment;
		
	} else
		for(size_t j=34;j<68;j++)
			I += people.at(j).size();
	
	/* Calculate sum of S(a,s) and IRR(a,s) */
	double S = 0;
	for(size_t j=0;j<34;j++)
		S += people.at(j).size() * IRR[j];
	
	if(S > 0) {
	
		/* Calculate lambda */
		double lambda = 0;
		lambda = (GetBeta() * I) / S;
		
		/* Find Incidence(a,s) */
		for(size_t j=0;j<34;j++)
			incidence[j] = Round(lambda * people.at(j).size() * IRR[j]);
		
		/* Printing out for convenience */
		double Susceptibles = 0;
		double Inc = 0;
		double Infections = 0;
		for(size_t j=0;j<34;j++) {
			Susceptibles += people.at(j).size();
			Inc += incidence[j];
		}
		for(size_t j=34;j<68;j++)
			Infections += people.at(j).size();
		
		cout << "Time = " << theQ->GetTime() / 365.25 << endl;
		cout << "PopSize = " << populationSize << endl;
		cout << "I = " << I << endl;
		cout << "S*IRR = " << S << endl;
		cout << "lambda = " << lambda << endl;
		cout << "Infections = " << Infections << endl;
		cout << "S = " << Susceptibles << endl;
		cout << "Incidence = " << Inc << endl;
		cout << endl;

		/* Randomly pick cases */
		for(size_t j=0;j<34;j++)
			if(incidence[j] != 0 && incidence[j] < people.at(j).size())
				RandomiseInfection(incidence[j],j,people.at(j));
	}
	
	/* Reset incidence count */
	incidentCases = 0;
}

/////////////////////
/////////////////////

void population::RandomiseInfection(const int theSize, const size_t theRow, vector<person *> theVector)
{
	/* Shuffle theVector (by value ONLY, not by reference) */
	random_shuffle(theVector.begin(),theVector.end(),Random);
	
	for(size_t i=0;i<theSize;i++) {
		new Infection(people.at(theRow).at(theVector.at(i)->GetPersonIndex()),theQ->GetTime() + (theRng->doub() * 365.25));
	}
}

/////////////////////
/////////////////////
