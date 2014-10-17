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
	person(const double Time); //constuctor
	virtual ~person(); //destructor
	
	/* Initialiser functions */
	double AssignGender();
	void AssignInitialAge(const double Time);
	double AssignNatDeathDate(const double Time);
	
	/* Methods */
	void Kill(double Time);
	double SetAge(double Time);
	void SetDiagnosedState(const bool theState) { diagnosed = theState; }
	void SetCd4TestState(const bool theState) { cd4Test = theState; }
	
	/* Accessor methods */
	bool GetGender() const;
	double GetNatDeathDate() const;
	bool Alive();
	double GetAge() const;
	bool GetDiagnosedState() const { return diagnosed; }
	bool GetCd4TestState() const { return cd4Test; }
	const double GetBirthDay() const { return BirthDay; }
	
private:
	/* basic characteristics */
	double gender;
	double currentAge;
	double initialAge;
	double natDeathDate;
	
	/* HIV status */
	double seroStatus;
	double hivDeathDate;
	
	/* Day = time an event occured */
	double DeathDay;
	const double BirthDay;
	
	/* HIV care */
	bool diagnosed;
	bool inCare;
	bool cd4Test;
	bool cd4Result;
	bool art;
};

#endif /* defined(__priorityQ__person__) */