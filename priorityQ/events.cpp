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
#include "person.h"

//extern person * thePerson;


using namespace std;

/////////////////////
/////////////////////

Death::Death(person * const thePerson, const double Time) :
event(Time),
iPerson(thePerson)
{}

Death::~Death()
{}

void Death::Execute()
{
	cout << "Death executed." << endl;
	iPerson->Kill(eventTime);
}

/////////////////////
/////////////////////

HivTest::HivTest(const double Time) : event(Time)
{}

HivTest::~HivTest()
{}

void HivTest::Execute()
{
	cout << "HivTest executed." << endl;
};

/////////////////////
/////////////////////

Cd4Test::Cd4Test(const double Time) : event(Time)
{}

Cd4Test::~Cd4Test()
{}

void Cd4Test::Execute()
{
	cout << "Cd4Test executed." << endl;
};