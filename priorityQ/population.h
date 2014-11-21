//
//  population.h
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__population__
#define __priorityQ__population__

#include <stdio.h>
#include <vector>

class person;

using namespace std;

class population {
public:
	population(const double theSize); //constructor
	~population(); //destructor
	
	/* Methods */
	void Generate();
	
	/* Vector Methods */
	void InitialiseVector();
	void AddPerson(person * thePerson);
	void RemovePerson(person * thePerson);
	void UpdateVector(person * thePerson);		
	void PushInVector(person * thePerson);
	void SwapOutVector(person * thePerson);
	
	/* Infectiousness Methods */
	void UpdateArray(person * const thePerson);
	void PushInArray(person * const thePerson);
	void SwapOutArray(person * const thePerson);
	
	/* Accessor Methods */
	double GetReferenceYear() const { return referenceYear; }
	double GetBeta() const { return beta; }
	
	/* Incidence Calculation */
	double GetWeightedTotal() const;
	unsigned int GetInfectedCases();
	void CalculateBeta();
	void CalculateIncidence();
	void RandomiseInfection(const int theSize, const size_t theRow, vector<person *> theVector);
	void AddCase() { incidentCases++; }
	
private:
	const double sizeAdjustment;
	unsigned int populationSize;
	
	/* VectorVector */
	vector<vector<person *> > people;
	
	/* Infectiousness Array */
	unsigned int infectiousness[5];
	
	unsigned int incidentCases;
	double const referenceYear;
	double beta;
};

#endif /* defined(__priorityQ__population__) */
