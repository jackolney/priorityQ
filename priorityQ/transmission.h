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

using namespace std;

class Transmission {
public:
	Transmission(); //constructor
	~Transmission(); //destructor
	
	/* Methods */
	void UpdateVector(person * const thePerson);
	void PushToVector(person * const thePerson);
	void RemoveFromVector(person * const thePerson);
	
	void CalculateBeta();
	void SetBeta(const double theValue) { beta = theValue; }
	
	/* Accessor Methods */
	size_t GetVectorSize_Art() const;
	size_t GetVectorSize_Cd4_4() const;
	size_t GetVectorSize_Cd4_3() const;
	size_t GetVectorSize_Cd4_2() const;
	size_t GetVectorSize_Cd4_1() const;
	
	double GetReferenceYear() const { return referenceYear; }
	double GetWeightedTotal() const;
	double GetBeta() const { return beta; }
	double GetIncidenceWeight() const;
	
private:
	/* Vectors */
	vector<person*> pPersonCounter_Art;
	vector<person*> pPersonCounter_Cd4_4;
	vector<person*> pPersonCounter_Cd4_3;
	vector<person*> pPersonCounter_Cd4_2;
	vector<person*> pPersonCounter_Cd4_1;
	
	double const referenceYear;
	double beta;
};


#endif /* defined(__priorityQ__transmission__) */
