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
	void Generate(const double theSize);
	void AddPerson(person * thePerson);
	void RemovePerson(person * thePerson);
	
	/* Vector methods */
	void InitialiseVector();
	void UpdateVector(person * thePerson);
	void PushIn(person * thePerson);
	void SwapOut(person * thePerson);
//	void GetVectorSize();
	
	/* Incidence */
	void CalculateIncidence();

private:
	const double sizeAdjustment;
	unsigned int populationSize;
	
	/* VectorVector */
	vector<vector<person *> > people;

};

#endif /* defined(__priorityQ__population__) */
