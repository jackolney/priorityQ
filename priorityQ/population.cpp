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
#include "events.h"
#include "toolbox.h"

Transmission * theTrans;
//Incidence * theInc;
Cd4Counter * theCd4Counter;

extern eventQ * theQ;

population::population(const double theSize) : sizeAdjustment(theSize)
{
	Generate(sizeAdjustment);
	InitialiseVector();
	CreateOutputArray();
	ScheduleIncidence(this);
//	theInc = new Incidence; //Need to be removed... but first kill all of the functions it calls downstream.
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

	cout << "Guy in. PersonIndex = " << people.at(i).size() << " RowIndex = " << i << endl;
	
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

void population::RemovePerson(person * thePerson)
{
	cout << "DEATH." << endl;
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
//	if(thePerson->GetSeroStatus()) {
	cout << "Guy to go out ..." << endl;
	cout << "Time = " << theQ->GetTime() / 365.25 << endl;
	cout << "RowIndex = " << thePerson->GetRowIndex() << endl;
	if(thePerson->GetPersonIndex() >= people.at(thePerson->GetRowIndex()).size())
	   cout << "BIG ERROR." << endl;
	cout << "PersonIndex = " << thePerson->GetPersonIndex() << endl;
	cout << "NatDeathDate = " << people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex())->GetNatDeathDate() << endl;
	cout << "RowSize = " << people.at(thePerson->GetRowIndex()).size() << endl << endl;
//	}

	if(thePerson->GetPersonIndex() == people.at(thePerson->GetRowIndex()).back()->GetPersonIndex()) {
		people.at(thePerson->GetRowIndex()).back() = NULL;
		people.at(thePerson->GetRowIndex()).pop_back();
	} else {
		people.at(thePerson->GetRowIndex()).back()->SetRowIndex(thePerson->GetRowIndex());
		cout << "oldPersonIndex = " << people.at(thePerson->GetRowIndex()).back()->GetPersonIndex() << endl;
		people.at(thePerson->GetRowIndex()).back()->SetPersonIndex(thePerson->GetPersonIndex());
		cout << "newPersonIndex = " << people.at(thePerson->GetRowIndex()).back()->GetPersonIndex() << endl;
		people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex()) = people.at(thePerson->GetRowIndex()).back();
		people.at(thePerson->GetRowIndex()).pop_back();
	}
	
	if(thePerson->GetPersonIndex() >= people.at(thePerson->GetRowIndex()).size())
		cout << "ALERT." << endl;

//	people.at(thePerson->GetRowIndex()).
	cout << "RowSizeNow = " << people.at(thePerson->GetRowIndex()).size() << endl << endl;
	
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
	double incidence[34];
	for(size_t j=0;j<34;j++)
		incidence[j] = 0;
	
	/* Find total number of infected (I) */
	unsigned int I = 0;
	for(size_t j=34;j<68;j++) {
		I += people.at(j).size();
	}
	
	/* Calculate sum of S(a,s) and IRR(a,s) */
	double S = 0;
	for(size_t j=0;j<34;j++)
		S += people.at(j).size() * IRR[j];
	
	cout << "PopSize = " << populationSize << endl;
	
	if(S != 0) {
	
		/* Calculate little i */
		double i = 0;
		i = I / S;

		/* Find Incidence(a,s) */
		for(size_t j=0;j<34;j++)
			incidence[j] = Round(i * people.at(j).size() * IRR[j]);
		
		/* Seed initial infection in 1975 */
		if(theQ->GetTime() == 5 * 365.25)
			for(size_t j=0;j<34;j++)
				if(people.at(j).size() > 10)
					incidence[j] += 10;
		
		/* A whole bunch of checks */
//		cout << "Incidence";
//		for(size_t j=0;j<34;j++)
//			cout << " [" << j << "] = " << incidence[j];
//		cout << endl;
	
		// Then we need to randomly pick these buggers.
		// Schedule infection in them.
		
		/* Printing out for convenience */
		double Sus = 0;
		double Inf = 0;
		for(size_t j=0;j<34;j++) {
			Sus += people.at(j).size();
			Inf += incidence[j];
		}
		cout << "Time = " << theQ->GetTime() / 365.25 << endl;
		cout << I << " = Total infections." << endl;
		cout << Sus << " = S." << endl;
		cout << Inf << " = NewInfections." << endl;
		cout << endl;

		/* Randomly pick cases */
		for(size_t j=0;j<34;j++)
			if(incidence[j] != 0)
				GetCases(incidence[j],j,people.at(j));
	}
}

/////////////////////
/////////////////////

void population::GetCases(const int theSize, const size_t theRow, vector<person *> & theVector)
{
		//Setup output array values.
	unsigned long output[theSize];
	for(size_t i=0;i<theSize;i++)
		output[i] = 0;
	
	cout << theSize << " = theSize." << endl;
	cout << theVector.size() <<  " = theVector->size()." << endl;
	cout << "The Row = " << theRow << endl;
	cout << "Before." << endl;
	for(size_t i=0;i<theVector.size();i++)
		cout << theVector.at(i)->GetPersonIndex() << " ";
	cout << endl;
	
	random_shuffle(theVector.begin(),theVector.end(),Random);
	
	cout << "After." << endl;
	for(size_t i=0;i<theVector.size();i++)
		cout << theVector.at(i)->GetPersonIndex() << " ";
	cout << endl;
	
	cout << "Output." << endl;
	for(size_t i=0;i<theSize;i++) {
		output[i] = theVector.at(i)->GetPersonIndex();
		cout << output[i] << " ";
		new Infection(people.at(theRow).at(output[i]),theQ->GetTime());
	}
	cout << endl;
}

/////////////////////
/////////////////////
