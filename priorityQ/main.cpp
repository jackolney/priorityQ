//
//  main.cpp
//  priorityQ
//
//  Created by Jack Olney on 23/08/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include <mach/mach_time.h>
#include "rng.h"
#include "person.h"
#include "population.h"
#include "cohort.h"
#include "event.h"
#include "events.h"
#include "eventQ.h"

using namespace std;

/* Pointers to core stuff */
Rng * theRng;
eventQ * theQ;
extern double * pTheDALY;

int main(int argc, const char * argv[])
{
	
	/* Keeps the output window open */
	D(cout << "Starting code." << endl << endl);
	
	/* Declare RandomNumberGenerator */
	theRng = new Rng(mach_absolute_time());
//	theRng = new Rng(1); //Fixed seed for testing.

	/* Define the event queue */
	theQ = new eventQ(0,1e+06*365.25); //constructor takes the parameters of startTime and stopTime.

	/* Create new cohort of individuals */
	new population(1);

	/* Model Run */
	theQ->RunEvents();
	
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
	//		-> cohort constructor defines a startTime = Done.
	//		-> startTime then entered into theQ = Done.
	//		-> at the correct time theQ calls cohort->GeneratreCohort(); = Done.
	// 14) Stagger start of individuals in each cohort (spread throughout the year). = Done.
	//		-> Stagger over the period of one year. = Done.
	//		-> Make sure age / death date / events are all ON TOP of this date. = Done.
	// 15) Multiple cohorts over time. <- TARGET! = Done.
	// 16) Age structure in 1970 for time == 0. = Done.
	// 17) Allow events to be cancelled. = Done.
	// 18) Seed HIV incidence.
	//		-> Create hiv.h and Hiv(). = Done.
	//		-> Schedule HivIncidence each year. = Done.
	// 19) How to handle multiple events occuring on the same day? (non-issue).
	// 20) Allow person to be part of a COHORT. = Done.
	// 21) Scope to allow HIV to be acquired sometime during the year. = Done.
	// 22) EXPAND to include all functions of the model.
	//		-> Only allow Cd4Testing if HIV-positive. = Done.
	//		-> Ensure that I reuse as much code as possible.
	//
	//			---------------------------------------------------------------------------------------------------------------------------------------------
	//			>> NATURAL HISTORY: 
	//				-> UpdateCd4Count() = Done.
	//				-> UpdateWhoStage() = Done.
	//				-> ForArtToo... ensure that disease progression occurs properly. = Done.
	//				-> Flags for checking too? = Done.
	//				-> Each event with competing events supplies additional info to the event which is checked in CheckValid() prior to Execute(); = Done.
	//				-> Put DATE for NH events in constructors for events?. = Done.
	//				-> CHECK THAT WHEN ON ART... REVERSE HAPPENS AS EXPECTED. = Done.
	//			---------------------------------------------------------------------------------------------------------------------------------------------
	//			>> CASCADE:
	//				-> HivTesting (HCT / VCT / PICT); = Done.
	//					-> Separate events for each Test. Execute() specifies time delay and probability of entering Care and receiving CD4 test. = Done.
	//				-> Cd4Testing (care etc.) = Done.
	//					-> ONE EVENT for all CD4 testing. -> Need a testing route flag on person (for retention purposes). = Done.
	//				-> Cd4Results = Done.
	//				-> LTFU. (in progress).
	//				-> Pre-ART Care Retention. = Done.
	//				-> ART Initiation. = Done.
	//				-> ART dropout. = Done.
	//				-> Update AGE in each step ( I think I need to apply this to NH and Cascade events ). = Done.
	//				-> Ensure that as patient becomes symptomatic a PICT trigger is enabled. (and cascade event triggers). = Done.
	//				-> Check that all times and proportions are correct. = Done.
	//				-> ART Adherence (challenge). = Done.
	//			---------------------------------------------------------------------------------------------------------------------------------------------
	//			>> OUTPUT METRICS: (how to calculate? per person? or by year and across the population?)
	//				-> DALYs between 2010 and 2030. = Done.
	//				-> Cost between 2010 and 2030.
	//				-> Care experience of those died between 2010 and 2030.
	//			---------------------------------------------------------------------------------------------------------------------------------------------
	//			>> R-TOOLS:
	//				-> Specific functions that will run theQ->RunEvents() with a different set of parameters and spit-back different things (DALYs or COST etc.)
	//
	//
	//			---------------------------------------------------------------------------------------------------------------------------------------------
	//			>> INTERVENTIONS:
	//				-> Include 12 interventions.
	//				-> Intervention scenarios.
	//			---------------------------------------------------------------------------------------------------------------------------------------------
	//
	//			-> An HIV-test through ANY route (each route should have a separate event but should all call a HivTest function.
	//		-> Need a more solid end point (break;) in the code
	//			-> Inclusion of HIV-related death date.
	//		-> Make more use of Cancel() for overriding competing hazards in the model.
	//		-> Costs / DALYs - can I calculate costs from the clinic perspective?
	
	/* PLAYGROUND. (who needs Swift?) */
	
	for(size_t i = 0; i<20; i++)
		cout << pTheDALY[i] << endl;
	
	
	/* Empty eventQ at end of run */
	while(!theQ->Empty())
		theQ->PopTop();

    return 0;
}


/*NOTES*/

// Consider output metrics from the model.
// Endtime of theQ may be overkill, we want everyone to die first ->> may cause longterm issues.
// Be mindful of eventual need to input parameter values / Rtools inclusion and interaction through R.
