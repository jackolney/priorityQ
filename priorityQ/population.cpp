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

population::population(unsigned const int theSize) : populationSize(theSize)
{
	Generate(populationSize); //cheeky?
}

population::~population()
{}

void population::Generate(unsigned const int theSize)
{
		//Function to generate list of cohorts to be created.
	
//	double yr = 0;
//	int cohortArray [2] = {2,1};
	
	double popIncrease [61] = {1,1.0360,1.0365,1.0370,1.0373,1.0376,1.0378,1.0380,1.0382,1.0384,1.0387,1.0389,1.0390,1.0388,1.0384,1.0379,1.0373,1.0366,1.0359,1.0352,1.0344,1.0337,1.0330,1.0320,1.0308,1.0294,1.0280,1.0269,1.0262,1.0261,1.0265,1.0269,1.0272,1.0274,1.0274,1.0273,1.0272,1.0271,1.0270,1.0271,1.0272,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274,1.0274};
	
	unsigned const int initialPopulationSize = 100;
	unsigned int cumulativeTotal [61] = {0};
	unsigned int popSize [61];
	
	for(size_t i = 0; i < 60; i++) {
		if(i == 0) {
			cumulativeTotal[i] = initialPopulationSize * 1000;
			popSize[i] = initialPopulationSize * 1000;
		} else {
			cumulativeTotal[i] = cumulativeTotal[i-1] * popIncrease[i];
			popSize[i] = cumulativeTotal[i] - cumulativeTotal[i-1];
		}
	}

	
	
		//Allow populationSize to scale the cohort size.
		//Use a loop to multiply all elements of an array by populationSizeScalar.
	
//	for(int i = 0; i < 2; i++) {
//		new cohort(cohortArray[i],yr);
//		yr += 10;
//	}
}