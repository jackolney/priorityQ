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

Transmission * theTrans;
Incidence * theInc;

population::population(const double theSize) : populationSize(theSize)
{
	Generate(populationSize);
	CreateOutputArray();
	theInc = new Incidence;
	theTrans = new Transmission;	
}

population::~population()
{}

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
//	double yr = 0;
//	for(int i = 0; i < 60; i++) {
//		new cohort(popSize[i],yr);
//		yr += 10;
//	}

	
		//TEMPORARY TESTING PLATFORM//
	
	double yr = 0; //specifiees startTime for individuals.
	int cohortArray [1] = {1};

//	Allow populationSize to scale the cohort size.
//	Use a loop to multiply all elements of an array by populationSizeScalar.
	
	for(int i = 0; i < 1; i++) {
		new cohort(cohortArray[i],yr);
		yr += 365;
	}
}