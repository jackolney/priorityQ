//
//  population.cpp
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "population.h"
#include "cohort.h"

population::population(unsigned const int theSize) : populationSize(theSize)
{}

population::~population()
{}

void population::Generate()
{
		//Function to generate list of cohorts to be created.
		//Will walk along an array and spit out the corresponding cohorts at the beginning of the Model.
	double yr = 0;
	int cohortArray [2] = {1,1};
		//Could do something with the arguement populationSize?
	
	for(int i = 0; i < 2; i++) {
		new cohort(cohortArray[i],yr);
		yr += 365.25;
	}
}