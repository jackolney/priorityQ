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

/* Test Function to be pointed to */
void testFunc()
{
	cout << "Hello, Jack. This function worked, aren't you clever." << endl;
}

/////////////////////
/////////////////////


void HivTest::Execute()
{
	cout << "HivTest executed." << endl;
};

HivTest::HivTest(const double Time, void (*funcAddr)()) : event(Time,funcAddr)
{}

HivTest::~HivTest()
{}

/////////////////////
/////////////////////

void Cd4Test::Execute()
{
	cout << "Cd4Test executed." << endl;
};

Cd4Test::Cd4Test(const double Time, void (*funcAddr)()) : event(Time,funcAddr)
{}

Cd4Test::~Cd4Test()
{}