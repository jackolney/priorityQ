//
//  main.cpp
//  priorityQ
//
//  Created by Jack Olney on 23/08/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include <mach/mach_time.h>
#include "rng.h"
#include "person.h"
#include "cohort.h"
#include "event.h"
#include "events.h"
#include "eventQ.h"

using namespace std;

/* Pointers to things (allows me to access them elsewhere with extern) */
Rng * theRng;
eventQ * theQ;
cohort * theCohort;


int main(int argc, const char * argv[])
{
	
	/* Keeps the output window open */
	cout << "Starting code." << endl;

	/* Declare RandomNumberGenerator */
	theRng = new Rng(mach_absolute_time());

	/* Define the event queue */
	theQ = new eventQ(0,1e+06*365.25); //constructor takes the parameters of startTime and stopTime.

	/* Create new cohort of individuals */
	cohort * theCohort = new cohort(10);
	theCohort->GenerateCohort(0);
	
	/* Ask a few questions on object sizes */
	cout << "Cohort size = " << theCohort->GetCohortSize() << endl;
	cout << "Q size = " << theQ->Size() << endl;
	cout << "Container length = " << theCohort->cohortContainer.size() << endl;

	/* Model Run */
	cout << "Start time = " << theQ->GetTime() << endl;
	
	theQ->RunEvents();
	
	cout << "End time = " << theQ->GetTime() << endl;

	/* Check that everyone is dead */
	for(size_t i = 0; i < theCohort->cohortContainer.size(); i++)
	{
		cout << "All dead? = " << theCohort->cohortContainer[i]->Alive() << endl;
	}

	cout << "Size of the priority queue = " << theQ->Size() << endl;
	
	/*CHALLENGE*/
	
	// 1) Pull out the top() etc. = Done.
	// 2) Pull out multiple tops(), ensuring that they are being ordered correctly. = Done.
	// 3) Test out including function pointers in here too. = Done.
	// 4) Transition to multiple cpp files. = Done.
	// 5) Supply time and function reference in event class constructor. = Done.
	// 5) Including a "currentTime" we walk through time and execute the top of the queue, pop it off and continue. = Done.
	// 6) Include a PERSON. = Done.
	// 7) Assign characteristics to an instance of person at initialisation. = Done.
	// 8) Allow events (derived from class event) to act upon person. = Done.
	// 9) Run two people on one eventQ with a GlobalTime. = Done.
	// 10) Set up ages to run properly. = Done.
	// 11) DeathDates should be MINUS initialAge (convert to days too). = Done.
	// 12) Allow UpdateQ() to run -> perhaps to remote functions. = Done.
	// 13) Allow cohorts to be fired off at different times. <- CHALLENGE NOW.
	// 14) Stagger start of individuals in each cohort (spread throughout the year).
	// 15) Allow events to be cancelled.
	// 16) How to handle multiple events occuring on the same day?
	// 17) Allow person to be part of a COHORT.
	// 18) EXPAND to include all functions of the model.
	
	theQ->Empty(); //Empty eventQ at end of run.

    return 0;
}


/*NOTES*/

// Will create this model for one individual
// Transistion into defining an array of pointers (of class event) to an array of pointers (of class event Q) to corresponding eventQ's. Therefore allowing me to simulate mulitple individuals simultaneously.

// All events.h classes inherit attributes from event.h
// Ell events have an Execute() which takes NO arguments.

/* Rules to implement */
// 1) Require a GlobalTime variable
// 2) One eventQ -> theQ.
// 3) One cohort of people run per year
// 4) ALL persons feed events into the queue which then executes over time. All individuals run on same time, BUT do not interact (yet).