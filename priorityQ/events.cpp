//
//  events.cpp
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "events.h"
#include "event.h"

using namespace std;

/////////////////////
/////////////////////


void HivTest::Execute()
{
	cout << "HivTest executed." << endl;
};

HivTest::HivTest(const double Time) : event(Time)
{}

HivTest::~HivTest()
{}

/////////////////////
/////////////////////

void Cd4Test::Execute()
{
	cout << "Cd4Test executed." << endl;
};

Cd4Test::Cd4Test(const double Time) : event(Time)
{}

Cd4Test::~Cd4Test()
{}