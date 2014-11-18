//
//  transmission.h
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__transmission__
#define __priorityQ__transmission__

#include <vector>
#include <stdio.h>
#include "person.h"
#include "event.h"
#include "population.h"

using namespace std;

class Transmission {
public:
	Transmission(population * thePop); //constructor
	~Transmission(); //destructor
	
	/* Methods */
	void UpdateVector(person * const thePerson);
	void PushIn(person * const thePerson);
	void SwapOut(person * const thePerson);
	
	void CalculateBeta();
	
	/* Accessor Methods */	
	double GetReferenceYear() const { return referenceYear; }
	double GetWeightedTotal() const;
	double GetBeta() const { return beta; }
	
private:
	/* Array */
	unsigned int PersonCounter[5];
	
	population * pPop;
	double const referenceYear;
	double beta;
};

#endif /* defined(__priorityQ__transmission__) */
