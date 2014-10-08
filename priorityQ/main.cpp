//
//  main.cpp
//  priorityQ
//
//  Created by Jack Olney on 23/08/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;


	/*Event definition */
class event {
public:
	//	testClass();	//Constructer [not neccessary at the moment]
	//	~testClass();	//Destructer  [not neccessary at the moment]
	
	double time = 0; //define time - make private eventually.
	void (*p_fun)(); //function pointer - make private eventually.
	
	// Include a "GetTime()" when private.
	// Include a "GetFun()" when private.
	
	
};


	/*Define operator() for comparison class*/
struct timeComparison {
	bool operator()(const event *lhs, const event *rhs) const
	{
		return lhs->time > rhs->time;
	}
};

	/*Define eventQ class*/
class eventQ {
public:
//	eventQ();
//	~eventQ();
	
	/*methods*/
	void Add(event * const theEvent);
	//Jeff has a Run() here that walks through events.
	
	/*accessor methods*/
	//Size
	//Empty
	//GetTime
	
	/*methods*/
	event * GetTop();
	
	priority_queue<event*, vector<event*>, timeComparison> iQ;
	//Can include a currentTime;
	
};

	/*Define Add()*/
void eventQ::Add(event * const theEvent)
{
	iQ.push(theEvent);
	
	return;
}

	/*Define GetTop()*/
event * eventQ::GetTop()
{
	event * theEvent = iQ.top();
//	iQ.pop();
	return theEvent;
}


int main(int argc, const char * argv[])
{

	/*Print Hello*/
	cout << "Hello, Jack!" << endl;
	
	/*Define the event queue*/
	eventQ testQ;

	/*Create event*/
	event * testEvent;
	/*Give event a time*/
	testEvent->time = 10;
	
//	cout << testEvent->time << endl;
	
	/*Add event to the Q*/
	testQ.Add(testEvent);
	
	/*Access top of the queue*/
	cout << testQ.GetTop()->time << endl;
	
	
	/*CHALLENGE*/
	
	// 1) Pull out the top() etc. EXPAND! GO GO GO!
	// 2) To pull out the top() need a function in eventQ to get the top of the Q -> see Jeff's code.
	// 3) Test out including function pointers in here too.
	// 4) Transition to multiple cpp files.
	// 5) Including a "currentTime" we walk through time and execute the top of the queue, pop it off and continue.
	// 6) EXPAND to include all functions of the model.

    return 0;
}


/*NOTES*/

// Will create this model for one individual
// Transistion into defining an array of pointers (of class event) to an array of pointers (of class event Q) to corresponding eventQ's. Therefore allowing me to simulate mulitple individuals simultaneously.
