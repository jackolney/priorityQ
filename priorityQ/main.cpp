//
//  main.cpp
//  priorityQ
//
//  Created by Jack Olney on 23/08/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "event.h"
#include "eventQ.h"

using namespace std;



	/* Test Function to be pointed to */
void testFunc() {
	cout << "Hello, Jack. This function worked, aren't you clever." << endl;
}


int main(int argc, const char * argv[])
{

	/* Print Hello */
	cout << "Hello, Jack!" << endl;
	
	/* Define the event queue */
	eventQ testQ;

	/* Create event and provide time to constructor */
	event * testEvent1 = new event(20); //Needs to be created on the heap so that (a) I can assign a time to the constructor and (b) allows me to destroy it later.
	event * testEvent2 = new event(5);
	
	/* Point function pointer to address of desired function */
	testEvent1->ptr_fun = &testFunc;
	testEvent2->ptr_fun = &testFunc;
	
	/* Access time */
	cout << testEvent1->GetTime() << endl;
	cout << testEvent2->GetTime() << endl;
	
	/* Add event to the Q */
	testQ.AddEvent(testEvent1);
	testQ.AddEvent(testEvent2);
	
	/* Access top of the queue */
	cout << testQ.GetTop()->GetTime() << endl;
	cout << testQ.Size() << endl;
	testQ.GetTop()->ptr_fun();

	testQ.PopTop();

	cout << testQ.GetTop()->GetTime() << endl;
	cout << testQ.Size() << endl;
	testQ.GetTop()->ptr_fun();
	
	
	/*CHALLENGE*/
	
	// 1) Pull out the top() etc. = Done.
	// 2) Pull out multiple tops(), ensuring that they are being ordered correctly. = Done.
	// 3) Test out including function pointers in here too. = Done.
	// 4) Transition to multiple cpp files. = Done.
	// 5) Supply time and function reference in event class constructor.
	// 5) Including a "currentTime" we walk through time and execute the top of the queue, pop it off and continue.
	// 6) EXPAND to include all functions of the model.

    return 0;
}


/*NOTES*/

// Will create this model for one individual
// Transistion into defining an array of pointers (of class event) to an array of pointers (of class event Q) to corresponding eventQ's. Therefore allowing me to simulate mulitple individuals simultaneously.
