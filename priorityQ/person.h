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
	
	/* Initialiser functions */
	double AssignGender();
	double AssignNatDeathDate();
	
	/* Methods */
	void Kill(double Time);
	
	/* Accessor methods */
	bool GetGender() const;
	double GetNatDeathDate() const;
	bool Alive();
	
	
private:
	double gender;
	double currentAge;
	double initialAge;
	double natDeathDate;
	
	double seroStatus;
	double hivDeathDate;
	
	/* Death */
	double DeathDay;
};

#endif /* defined(__priorityQ__person__) */