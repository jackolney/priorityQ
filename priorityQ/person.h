//
//  person.h
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__person__
#define __priorityQ__person__

#include <stdio.h>

class person {
public:
	person(const double startAge); //constuctor
	virtual ~person(); //destructor
	
	/* Accessor methods */
	bool GetGender();
	
	
private:
	double gender;
	double currentAge;
	double initialAge;
	double natDeathDate;
	
	double seroStatus;
	double hivDeathDate;
	
};

#endif /* defined(__priorityQ__person__) */