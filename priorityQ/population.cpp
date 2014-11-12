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

Transmission * theTrans;
Incidence * theInc;
Cd4Counter * theCd4Counter;

population::population(const double theSize) : sizeAdjustment(theSize)
{
	Generate(sizeAdjustment);
	InitialiseVectors();
	CreateOutputArray();
	theInc = new Incidence;
	theTrans = new Transmission;
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
//	double popIncrease [61] = {1,1.0360,1.0365,1.0370,1.0373,1.0376,1.0378,1.0380,1.0382,1.0384,1.0387,1.0389,1.0390,1.0388,1.0384,1.0379,1.0373,1.0366,1.0359,1.0352,1.0344,1.0337,1.0330,1.0320,1.0308,1.0294,1.0280,1.0269,1.0262,1.0261,1.0265,1.0269,1.0272,1.0274,1.0274,1.0273,1.0272,1.0271,1.0270,1.0271,1.0272,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274};
//
//	unsigned int cumulativeTotal [61];
//	unsigned int popSize [61];
//	
//	for(size_t i = 0; i < 60; i++) {
//		if(i == 0) {
//			cumulativeTotal[i] = theSize * 1000;
//			popSize[i] = theSize * 1000;
//		} else {
//			cumulativeTotal[i] = cumulativeTotal[i-1] * popIncrease[i];
//			popSize[i] = cumulativeTotal[i] - cumulativeTotal[i-1];
//		}
//	}
//
//	for(int i = 0; i < 60; i++)
//		new cohort(popSize[i],i * 365.25);

	
		//TEMPORARY TESTING PLATFORM//
	double yr = 0; //specifiees startTime for individuals.
	int cohortArray [1] = {1};
	
	for(int i = 0; i < 1; i++) {
		new cohort(cohortArray[i],yr);
		yr += 365;
	}
}

/////////////////////
/////////////////////

void population::InitialiseVectors()
{
	Susceptible.resize(34,vector<person *>(100));
	Infected.resize(34,vector<person *>(100));
}

void population::AddPerson(person * me)
{
	AddToVector(me);
	populationSize++;
}

void population::AddToVector(person * me)
{
	// 0to4,5to9,to14,to19,to24,to29,to34,to39,to44,to49,to54,to59,to64,to69,to74,to79,80
	unsigned int ageCatMax[17] = {4,9,14,19,24,29,34,39,44,49,54,59,64,69,74,79,200};
	unsigned int i = 0;
	while(me->GetAge() > ageCatMax[i] && i < 17)
		i++;
	
	if(me->GetGender())
		i += 17;

	if(!me->GetSeroStatus())
		Susceptible.at(i).push_back(me);
	else
		Infected.at(i).push_back(me);
}

/////////////////////
/////////////////////
