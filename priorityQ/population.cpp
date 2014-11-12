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
	InitialiseVector();
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
//		new cohort(this,popSize[i],i * 365.25);

	
		//TEMPORARY TESTING PLATFORM//
	double yr = 0; //specifiees startTime for individuals.
	int cohortArray [1] = {1};
	
	for(int i = 0; i < 1; i++) {
		new cohort(this,cohortArray[i],yr);
		yr += 365;
	}
}

/////////////////////
/////////////////////

void population::InitialiseVector()
{
		// Rows 0 to 33 are Susceptible.
		// Rows 34 to 67 are Infected.
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
	while(thePerson->GetAge() / 365.25 > ageCatMax[i] && i < 17)
		i++;
	
	if(thePerson->GetGender()) // If Male then i += 17;
		i += 17;
	
	if(thePerson->GetSeroStatus()) // If HIV-positive then i += 34;
		i += 34;
	
		// Therefore, i (rows) covers AGE and Susceptible/Infected.
	thePerson->SetPersonIndex(people.at(1).size());
	thePerson->SetRowIndex(1); // thePerson->SetAgeIndex(i);
	people.at(1).push_back(thePerson);
	
//	thePerson->SetPersonIndex(people.at(i).size());
//	thePerson->SetRowIndex(i);
//	people.at(i).push_back(thePerson);
}

void population::RemovePerson(person * thePerson)
{
		//Need to check the below... but it should grab thePerson and then switch it up with the guy at the end of the vector and pop_back();
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
	cout << endl << "people.at(" << thePerson->GetRowIndex() << ").size() = " << people.at(thePerson->GetRowIndex()).size() << endl;
	cout << "thePerson->GetRowIndex() = " << thePerson->GetRowIndex() << endl;
	cout << "thePerson->GetPersonIndex() = " << thePerson->GetPersonIndex() << endl;
	cout << "people.at(thePerson->GetRowIndex()).back()->GetRowIndex() = " << 	people.at(thePerson->GetRowIndex()).back()->GetRowIndex() << endl;
	cout << "people.at(thePerson->GetRowIndex()).back()->GetPersonIndex() = " << people.at(thePerson->GetRowIndex()).back()->GetPersonIndex() << endl;
	cout << "NatDeath (switch check) = " << people.at(thePerson->GetRowIndex()).back()->GetNatDeathDate() << endl;
	
	people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex()) = people.at(thePerson->GetRowIndex()).back();
	people.at(thePerson->GetRowIndex()).back()->SetRowIndex(thePerson->GetRowIndex());
	people.at(thePerson->GetRowIndex()).back()->SetPersonIndex(thePerson->GetPersonIndex());
	people.at(thePerson->GetRowIndex()).pop_back();
	
	cout << "Update..." << endl;
	cout << "people.at(" << thePerson->GetRowIndex() << ").size() = " << people.at(thePerson->GetRowIndex()).size() << endl;
	cout << "NatDeath (switch check) = " << people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex())->GetNatDeathDate() << endl;
	
	thePerson->SetRowIndex(NULL); //Doesn't actually set them to NULL
	thePerson->SetPersonIndex(NULL); //Doesn't actually set them to NULL
}

/////////////////////
/////////////////////
