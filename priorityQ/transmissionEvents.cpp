//
//  transmissionEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "transmissionEvents.h"

GetBeta::GetBeta(Transmission * const theTrans, const double Time) :
event(Time),
pTransmission(theTrans)
{}

GetBeta::~GetBeta()
{}

bool GetBeta::CheckValid()
{
	return true;
}

void GetBeta::Execute()
{
	pTransmission->CalculateBeta();
}