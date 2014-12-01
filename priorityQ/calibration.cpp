//
//  calibration.cpp
//  priorityQ
//
//  Created by Jack Olney on 01/12/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "calibration.h"

/* Calibration Pointers */
double * C1;
double * L21;
double * R3;
double * R8;
double * ART1;
double * ART2;
double * ART4;
double * ART5;
double * ART6;
double * ART9;
double * ART10;
double * ART11;
double * ART12;
double * ART13;
double * ART14;
double * pre2010;

void SeedCalibration(person * const thePerson, const double theTimeZero, const double theTimeOne, const double theTimeTwo, const double theTimeThree)
{
	if(thePerson->GetBirthDay() < theTimeZero)
		new TimeSplitZero(thePerson,theTimeZero);
	
	if(thePerson->GetBirthDay() < theTimeOne)
		new TimeSplitOne(thePerson,theTimeOne);
	
	if(thePerson->GetBirthDay() < theTimeTwo)
		new TimeSplitTwo(thePerson,theTimeTwo);
	
	if(thePerson->GetBirthDay() < theTimeThree)
		new TimeSplitThree(thePerson,theTimeThree);
}

/////////////////////
/////////////////////

TimeSplitZero::TimeSplitZero(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitZero::~TimeSplitZero()
{}

bool TimeSplitZero::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitZero::Execute()
{
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

TimeSplitOne::TimeSplitOne(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitOne::~TimeSplitOne()
{}

bool TimeSplitOne::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitOne::Execute()
{
	UpdateCalibrationArrayOne();
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

TimeSplitTwo::TimeSplitTwo(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitTwo::~TimeSplitTwo()
{}

bool TimeSplitTwo::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitTwo::Execute()
{
	UpdateCalibrationArrayTwo();
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

TimeSplitThree::TimeSplitThree(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitThree::~TimeSplitThree()
{}

bool TimeSplitThree::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitThree::Execute()
{
	UpdateCalibrationArrayThree();
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

void CreateCalibrationArray()
{
	C1 = new double[9];
	L21 = new double[36];
	R3 = new double[9];
	R8 = new double[9];
	ART1 = new double[48];
	ART2 = new double[9];
	ART4 = new double[3];
	ART5 = new double[3];
	ART6 = new double[9];
	ART9 = new double[3];
	ART10 = new double[3];
	ART11 = new double[3];
	ART12 = new double[3];
	ART13 = new double[9];
	ART14 = new double[9];
	pre2010 = new double[3];
	
	for(size_t i=0;i<48;i++) {
		if(i<3) {
			ART4[i] = 0;
			ART5[i] = 0;
			ART9[i] = 0;
			ART10[i] = 0;
			ART11[i] = 0;
			ART12[i] = 0;
			pre2010[i] = 0;
		}
		if(i<9) {
			C1[i] = 0;
			R3[i] = 0;
			R8[i] = 0;
			ART2[i] = 0;
			ART6[i] = 0;
			ART13[i] = 0;
			ART14[i] = 0;
		}
		if(i<36)
			L21[i] = 0;
		ART1[i] = 0;
	}
}

/////////////////////
/////////////////////

void UpdateCalibrationArrayOne()
{
	// C1;
	
	// L21;
	// R3;
	// R8;
	// ART1;
	// ART2;
	// ART4;
	// ART5;
	// ART6;
	// ART9;
	// ART10;
	// ART11;
	// ART12;
	// ART13;
	// ART14;
	// pre2010;
}

/////////////////////
/////////////////////

void UpdateCalibrationArrayTwo()
{
	
}

/////////////////////
/////////////////////

void UpdateCalibrationArrayThree()
{
	
}

/////////////////////
/////////////////////