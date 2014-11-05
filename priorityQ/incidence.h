//
//  incidence.h
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__incidence__
#define __priorityQ__incidence__

#include <stdio.h>
#include <vector>
#include "person.h"

using namespace std;

class Incidence {
public:
	Incidence(); //constructor
	~Incidence(); //destructor
	
	/* Methods */
	void UpdateIncidence(person * const thePerson);
	void ScheduleIncidenceReset(Incidence * const theInc);
	void ResetIncidence();
	
	/* Accessor Methods */
	size_t GetIncidenceVectorSize() const;
	
private:
	vector<person*> pIncidence;
};

#endif /* defined(__priorityQ__incidence__) */
