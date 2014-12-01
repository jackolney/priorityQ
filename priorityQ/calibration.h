//
//  calibration.h
//  priorityQ
//
//  Created by Jack Olney on 01/12/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__calibration__
#define __priorityQ__calibration__

#include <stdio.h>
#include "person.h"
#include "event.h"

void SeedCalibration(person * const thePerson, const double theTimeZero, const double theTimeOne, const double theTimeTwo, const double theTimeThree);

/////////////////////
/////////////////////

class TimeSplitZero : public event {
public:
	TimeSplitZero(person * const thePerson, const double Time); //constructor
	~TimeSplitZero(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class TimeSplitOne : public event {
public:
	TimeSplitOne(person * const thePerson, const double Time); //constructor
	~TimeSplitOne(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class TimeSplitTwo : public event {
public:
	TimeSplitTwo(person * const thePerson, const double Time); //constructor
	~TimeSplitTwo(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class TimeSplitThree : public event {
public:
	TimeSplitThree(person * const thePerson, const double Time); //constructor
	~TimeSplitThree(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

void CreateCalibrationArray();

void UpdateCalibrationArrayOne(person * const thePerson);

void UpdateCalibrationArrayTwo(person * const thePerson);

void UpdateCalibrationArrayThree(person * const thePerson);

#endif /* defined(__priorityQ__calibration__) */
