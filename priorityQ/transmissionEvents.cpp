//
//  transmissionEvents.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "transmissionEvents.h"

ScheduleBeta::ScheduleBeta(Transmission * const theTrans, const double Time) :
event(Time),
pTransmission(theTrans)
{}

ScheduleBeta::~ScheduleBeta()
{}

bool ScheduleBeta::CheckValid()
{
	return true;
}

void ScheduleBeta::Execute()
{
//	pTransmission->CalculateBeta();
}