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
#include "transmission.h"

using namespace std;

extern Transmission * theTrans;

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
	if(GetTime() == theTrans->GetReferenceYear()) {
		theTrans->CalculateBeta();
		pInc->ResetIncidence();
	} else
		pInc->ResetIncidence();
}