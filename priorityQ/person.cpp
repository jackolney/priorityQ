//
//  person.cpp
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "person.h"
#include "toolbox.h"

using namespace std;

person::person(const double startAge) : currentAge(startAge), initialAge(startAge), natDeathDate(0), seroStatus(0), hivDeathDate(0)
{
	gender = AssignGender();
	// assignNaturalDeathDate
}

person::~person()
{}

bool person::GetGender()
{
	return gender;
}