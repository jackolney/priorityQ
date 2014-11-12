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
#include "person.h"

using namespace std;

class population {
public:
	population(const double theSize); //constructor
	~population(); //destructor
	
	/* Methods */
	void Generate(const double theSize);
	void AddPerson(person * me);
	void AddToVector(person * me);
	
	/* Vector methods */
	void UpdateVector();
	
		//Vector of vectors (neater).
	vector<vector<person *> > Susceptible;
	vector<vector<person *> > Infected;
	void InitialiseVectors();
	
		//34 rows (17 for Female then 17 for Male);
		//100 columns? Can be pushed back using matrix.at(theRow).push_back(*someGuy);
	/* Age groups */
	// 0to4,5to9,to14,to19,to24,to29,to34,to39,to44,to49,to54,to59,to64,to69,to74,to79,80

private:
	const double sizeAdjustment;
	unsigned int populationSize;
	
	/* Vector */


		//Male and Female
		//Susceptible and Infected
};

#endif /* defined(__priorityQ__population__) */
