//
//  transmissionEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 18/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "transmissionEvents.h"
#include "transmission.h"

using namespace std;

extern Transmission * theTransmission;

PopulateTransmissionProbabilityVector::PopulateTransmissionProbabilityVector(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

PopulateTransmissionProbabilityVector::~PopulateTransmissionProbabilityVector()
{}

bool PopulateTransmissionProbabilityVector::CheckValid()
{
	return pPerson->Alive();
}

void PopulateTransmissionProbabilityVector::Execute()
{
	theTransmission->PushIn(pPerson);
}

/////////////////////
/////////////////////

BetaCalculation::BetaCalculation(const double Time) :
event(Time)
{
	cout << "BetaCalculation scheduled for = " << Time << endl;
}

BetaCalculation::~BetaCalculation()
{}

bool BetaCalculation::CheckValid()
{
	return true;
}

void BetaCalculation::Execute()
{
	theTransmission->CalculateBeta();
}
