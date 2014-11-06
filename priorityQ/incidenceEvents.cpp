//
//  incidenceEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "incidenceEvents.h"
#include "macro.h"

using namespace std;

SeedIncidence::SeedIncidence(Incidence * const theIncidence, const double Time) :
event(Time),
pInc(theIncidence)
{}

SeedIncidence::~SeedIncidence()
{}

bool SeedIncidence::CheckValid()
{
	return true;
}

void SeedIncidence::Execute()
{
	if(GetTime() == 32 * 365.25) {
		D(cout << "HEY HEY HEY." << endl);
//		pTransmission->CalculateBeta();
	} else
		pInc->ResetIncidence();
}