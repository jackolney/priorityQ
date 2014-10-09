//
//  main.cpp
//  priorityQ
//
//  Created by Jack Olney on 23/08/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "event.h"
#include "events.h"
#include "eventQ.h"

using namespace std;


int main(int argc, const char * argv[])
{
	
	/* Keeps the output window open */
	cout << "Starting code." << endl;
	
	/* Define the event queue */
	eventQ testQ(0,100); //constructor takes the paramters of startTime and stopTime.

	/* Schedule some events */
	event * testEvent1 = new HivTest(10);
	event * testEvent2 = new Cd4Test(20);
	
	/* Add events into priorityQ */
	testQ.AddEvent(testEvent1);
	testQ.AddEvent(testEvent2);
	
	cout << "Start time = " << testQ.GetTime() << endl;

	testQ.RunEvents();
	
	cout << "End time = " << testQ.GetTime() << endl;
	
//	/* Call top event */
//	testQ.GetTop()->Execute();
//	
//	/* PopTop */
//	testQ.PopTop();
//	
//	/* Call top event again */
//	testQ.GetTop()->Execute();
//
//	/* Size */
//	cout << testQ.Size() << endl;
	
	/*CHALLENGE*/
	
	// 1) Pull out the top() etc. = Done.
	// 2) Pull out multiple tops(), ensuring that they are being ordered correctly. = Done.
	// 3) Test out including function pointers in here too. = Done.
	// 4) Transition to multiple cpp files. = Done.
	// 5) Supply time and function reference in event class constructor. = Done.
	// 5) Including a "currentTime" we walk through time and execute the top of the queue, pop it off and continue.
	// 6) Include a PERSON upon which these functions can act.
	// 7) Allow person to be part of a COHORT.
	// 8) EXPAND to include all functions of the model.

    return 0;
}


/*NOTES*/

// Will create this model for one individual
// Transistion into defining an array of pointers (of class event) to an array of pointers (of class event Q) to corresponding eventQ's. Therefore allowing me to simulate mulitple individuals simultaneously.

// All events.h classes inherit attributes from event.h
// Ell events have an Execute() which takes NO arguments.
