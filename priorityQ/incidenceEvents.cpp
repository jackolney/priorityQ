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

SeedIncidence::SeedIncidence(Incidence * const theInc, const double Time) :
event(Time),
pInc(theInc)
{}

SeedIncidence::~SeedIncidence()
{}

bool SeedIncidence::CheckValid()
{
	return true;
}

void SeedIncidence::Execute()
{
	cout << pInc->GetIncidenceVectorSize() << endl;
	pInc->ResetIncidence();
	D(cout << "Incidence Reset." << endl);
}