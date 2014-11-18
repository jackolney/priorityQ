//
//  population.cpp
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "rng.h"
#include "population.h"
#include "cohort.h"
#include "output.h"
#include "update.h"
#include "eventQ.h"
#include "events.h"
#include "toolbox.h"

extern eventQ * theQ;
extern Rng * theRng;

population::population(const double theSize) : sizeAdjustment(theSize)
{
	Generate();
	InitialiseVector();
	CreateOutputArray();
	ScheduleIncidence(this);
}

population::~population()
{}

/////////////////////
/////////////////////

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

/////////////////////
/////////////////////

void population::InitialiseVector()
{
		// Rows 0 to 33 are Susceptible. Rows 34 to 67 are Infected.
	people.resize(68,vector<person *>(0));
}

void population::AddPerson(person * thePerson)
{
	PushIn(thePerson);
	populationSize++;
}

void population::RemovePerson(person * thePerson)
{
	SwapOut(thePerson);
	populationSize--;
}

void population::UpdateVector(person * thePerson)
{
	SwapOut(thePerson);
	PushIn(thePerson);
}

/////////////////////
/////////////////////

void population::PushIn(person * thePerson)
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
	
		// Therefore, i (rows) covers AGE and Susceptible/Infected.
	thePerson->SetPersonIndex(people.at(i).size());
	thePerson->SetRowIndex(i);
	people.at(i).push_back(thePerson);
	
		//Test print of people array.
//	if(thePerson->GetSeroStatus()) {
//		cout << endl;
//		cout << "theAge = " << theAge << endl;
//		cout << "Gender = " << thePerson->GetGender() << endl;
//		cout << "i = " << i << endl;
//		cout << "i - 34 = " << i - 34 << endl;
//		cout << "Susceptible..." << endl;
//		for(size_t i=0;i<34;i++)
//			cout << people.at(i).size() << endl;
//		cout << "Infected..." << endl;
//		for(size_t i=34;i<68;i++)
//			cout << people.at(i).size() << endl;
//		cout << endl;
//	}
}

/////////////////////
/////////////////////

void population::SwapOut(person * thePerson)
{
	people.at(thePerson->GetRowIndex()).back()->SetRowIndex(thePerson->GetRowIndex());
	people.at(thePerson->GetRowIndex()).back()->SetPersonIndex(thePerson->GetPersonIndex());
	people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex()) = people.at(thePerson->GetRowIndex()).back();
	people.at(thePerson->GetRowIndex()).pop_back();
	
		//Neccessary? as these guys get popped back anyway.
	thePerson->SetRowIndex(NULL); //Doesn't actually set them to NULL
	thePerson->SetPersonIndex(NULL); //Doesn't actually set them to NULL
}

/////////////////////
/////////////////////

void population::CalculateIncidence()
{
	/* IncidenceCases (M+F Total - Spectrum2014) & IRR (0 to 16 are Female, 17 to 33 are Male */
	const double IncCases[32] = {0,0,0,0,0,0,0,0,0,140,355,1134,1791,3418,6444,11887,21704,38623,66784,108993,165074,226131,269547,275327,243681,195612,152571,121318,101327,99767,93594,90036};
	const double IRR[34] = {0.000000,0.000000,0.000000,0.431475,0.979206,1.000000,0.848891,0.684447,0.550791,0.440263,0.336719,0.239474,0.167890,0.146594,0.171352,0.000000,0.000000,0.000000,0.000000,0.000000,0.244859,0.790423,1.000000,0.989385,0.854318,0.670484,0.493512,0.358977,0.282399,0.259244,0.264922,0.254788,0.164143,0.000000};

	/* Create incidence array (contains age and sex) */
	double incidence[34];
	for(size_t j=0;j<34;j++)
		incidence[j] = 0;

	/* Find total number of infected (I) */
	unsigned int I = 0;
	
	if(theQ->GetTime() < 32 * 365.25) {
	
		double yr [32];
		for(size_t i = 0; i<32; i++)
			yr[i] = 365.25 + (i * 365.25);
		
		unsigned int j = 0;
		while(theQ->GetTime() > yr[j] && j < 32)
			j++;
		
		I = IncCases[j] / sizeAdjustment;
		
	} else {
		for(size_t j=34;j<68;j++)
			I += people.at(j).size();
	}
	
	/* Calculate sum of S(a,s) and IRR(a,s) */
	double S = 0;
	for(size_t j=0;j<34;j++)
		S += people.at(j).size() * IRR[j];
	
	if(S != 0) {
	
		/* Calculate little i */
		double i = 0;
		i = I / S;

			//I need a BETA in here don't I?
		
		/* Find Incidence(a,s) */
		for(size_t j=0;j<34;j++)
			incidence[j] = Round(i * people.at(j).size() * IRR[j]);
		
		/* Printing out for convenience */
		double Sus = 0;
		double Inf = 0;
		double Cases = 0;
		for(size_t j=0;j<34;j++) {
			Sus += people.at(j).size();
			Inf += incidence[j];
		}
		for(size_t j=34;j<68;j++)
			Cases += people.at(j).size();
		
		cout << "PopSize = " << populationSize << endl;
		cout << "Time = " << theQ->GetTime() / 365.25 << endl;
		cout << I << " = I (changes pre/post 2002)." << endl;
		cout << Cases << " = Total infections." << endl;
		cout << Sus << " = S." << endl;
		cout << Inf << " = NewInfections." << endl;
		cout << endl;

		/* Randomly pick cases */
		for(size_t j=0;j<34;j++)
			if(incidence[j] != 0 && incidence[j] < people.at(j).size())
				GetCases(incidence[j],j,people.at(j));
	}
}

/////////////////////
/////////////////////

void population::GetCases(const int theSize, const size_t theRow, vector<person *> theVector)
{
	/* Shuffle theVector (by value ONLY, not by reference) */
	random_shuffle(theVector.begin(),theVector.end(),Random);
	
	for(size_t i=0;i<theSize;i++) {
		new Infection(people.at(theRow).at(theVector.at(i)->GetPersonIndex()),theQ->GetTime() + (theRng->doub() * 365.25));
	}
}

/////////////////////
/////////////////////
