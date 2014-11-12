//
//  cd4Counter.h
//  priorityQ
//
//  Created by Jack Olney on 10/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__cd4Counter__
#define __priorityQ__cd4Counter__

#include <vector>
#include <stdio.h>
#include "person.h"

using namespace std;

class Cd4Counter {
public:
	Cd4Counter(); //constructor
	~Cd4Counter(); //destructor
	
	/* Methods */
	void UpdateVector(person * const thePerson);
	void PushToVector(person * const thePerson);
	void RemoveFromVector(person * const thePerson);
	
	/* Accessor Methods */
	size_t GetCd4VectorSize_4() const;
	size_t GetCd4VectorSize_3() const;
	size_t GetCd4VectorSize_2() const;
	size_t GetCd4VectorSize_1() const;
	
private:
	/* Vectors */
	vector<person*> pCd4Counter_4;
	vector<person*> pCd4Counter_3;
	vector<person*> pCd4Counter_2;
	vector<person*> pCd4Counter_1;
};


#endif /* defined(__priorityQ__cd4Counter__) */
