//
//  population.cpp
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "population.h"
#include "cohort.h"
#include "output.h"
#include "transmission.h"
#include "incidence.h"
#include "cd4Counter.h"
#include "update.h"
#include "eventQ.h"

Transmission * theTrans;
Incidence * theInc;
Cd4Counter * theCd4Counter;
extern eventQ * theQ;

population::population(const double theSize) : sizeAdjustment(theSize)
{
	Generate(sizeAdjustment);
	InitialiseVector();
	CreateOutputArray();
	ScheduleIncidence(this);
	theInc = new Incidence; //Need to be removed... but first kill all of the functions it calls downstream.
	theTrans = new Transmission; //Need to be removed... but first kill all of the functions it calls downstream.
	theCd4Counter = new Cd4Counter;
}

population::~population()
{}

/////////////////////
/////////////////////

void population::Generate(const double theSize)
{
		//Function to generate list of cohorts to be created.
	
		/* Function to schedule cohorts over time (not being used until I scale everything up) */
	double popIncrease [61] = {1,1.0360,1.0365,1.0370,1.0373,1.0376,1.0378,1.0380,1.0382,1.0384,1.0387,1.0389,1.0390,1.0388,1.0384,1.0379,1.0373,1.0366,1.0359,1.0352,1.0344,1.0337,1.0330,1.0320,1.0308,1.0294,1.0280,1.0269,1.0262,1.0261,1.0265,1.0269,1.0272,1.0274,1.0274,1.0273,1.0272,1.0271,1.0270,1.0271,1.0272,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274};

	unsigned int cumulativeTotal [61];
	unsigned int popSize [61];
	
	for(size_t i = 0; i < 60; i++) {
		if(i == 0) {
			cumulativeTotal[i] = theSize * 1000;
			popSize[i] = theSize * 1000;
		} else {
			cumulativeTotal[i] = cumulativeTotal[i-1] * popIncrease[i];
			popSize[i] = cumulativeTotal[i] - cumulativeTotal[i-1];
		}
	}

	for(int i = 0; i < 60; i++)
		new cohort(this,popSize[i],i * 365.25);

	
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

void population::PushIn(person * thePerson)
{
	// 0to4,5to9,to14,to19,to24,to29,to34,to39,to44,to49,to54,to59,to64,to69,to74,to79,80
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
	thePerson->SetPersonIndex(people.at(0).size());
	thePerson->SetRowIndex(0);
	people.at(0).push_back(thePerson);
	
//	thePerson->SetPersonIndex(people.at(i).size());
//	thePerson->SetRowIndex(i);
//	people.at(i).push_back(thePerson);
	
		//Test print of people array.
//	if(thePerson->GetSeroStatus()) {
//		cout << endl;
//		cout << "Susceptible..." << endl;
//		for(size_t i=0;i<34;i++)
//			cout << people.at(i).size() << endl;
//		cout << "Infected..." << endl;
//		for(size_t i=34;i<68;i++)
//			cout << people.at(i).size() << endl;
//		cout << endl;
//	}
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

void population::SwapOut(person * thePerson)
{
	people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex()) = people.at(thePerson->GetRowIndex()).back();
	people.at(thePerson->GetRowIndex()).back()->SetRowIndex(thePerson->GetRowIndex());
	people.at(thePerson->GetRowIndex()).back()->SetPersonIndex(thePerson->GetPersonIndex());
	if(!people.at(thePerson->GetRowIndex()).empty())
		people.at(thePerson->GetRowIndex()).pop_back();

		//Neccessary?
	thePerson->SetRowIndex(NULL); //Doesn't actually set them to NULL
	thePerson->SetPersonIndex(NULL); //Doesn't actually set them to NULL
}

/////////////////////
/////////////////////

void population::CalculateIncidence()
{
	/* IRR (0 to 16 are Female, 17 to 33 are Male */
	const double IRR[34] = {0.000000,0.000000,0.000000,0.431475,0.979206,1.000000,0.848891,0.684447,0.550791,0.440263,0.336719,0.239474,0.167890,0.146594,0.171352,0.000000,0.000000,0.000000,0.000000,0.000000,0.244859,0.790423,1.000000,0.989385,0.854318,0.670484,0.493512,0.358977,0.282399,0.259244,0.264922,0.254788,0.164143,0.000000};

	/* Create incidence array (contains age and sex) */
	double incidence[34] = {};
	for(size_t j=0;j<34;j++)
		incidence[j] = 0;
	
	/* Find total number of infected (I) */
	unsigned int I = 1;
	for(size_t j=34;j<68;j++) {
		I += people.at(j).size();
	}

	cout << I << " = I." << endl;
	

	/* Calculate sum of S(a,s) and IRR(a,s) */
	double S = 0;
	for(size_t j=0;j<34;j++)
		S += people.at(j).size() * IRR[j];
	
	cout << S << " = S." << endl;
	
	if(S != 0 && I != 0) {
		
		/* Calculate little i */
		double i = 0;
		i = I / S;

		/* Find Incidence(a,s) */
		for(size_t j=0;j<34;j++)
			incidence[j] = i * people.at(j).size() * IRR[j];
			// Then we need to randomly pick these buggers and schedule infection in them!
		
		/* A whole bunch of checks */
		for(size_t j=0;j<34;j++)
			cout << "Incidence[" << j << "] = " << incidence[j] << endl;
		
		/* Printing out for convenience */
		double Sus = 0;
		for(size_t j=0;j<34;j++)
			Sus += people.at(j).size();
		
		double Inf = 0;
		for(size_t j=0;j<34;j++)
			Inf += incidence[j];
		
		cout << S << " = S." << endl;
		cout << Inf << " = Inf." << endl;
		
	}
}

/////////////////////
/////////////////////
