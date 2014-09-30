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

class event {
public:
	//	testClass();	//Constructer [not neccessary at the moment]
	//	~testClass();	//Destructer  [not neccessary at the moment]
	
	double time = 0; //define time - make private eventually.
	void (*p_fun)(); //function pointer - make private eventually.
	
	// Include a "GetTime()" when private.
	// Include a "GetFun()" when private.
	
	
};


// Define operator() for comparison class
struct timeComparison {
	bool operator()(const event *lhs, const event *rhs) const
	{
		return lhs->time > rhs->time;
	}
};

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

void eventQ::Add(event * const theEvent)
{
	iQ.push(theEvent);
	
	return;
}

event * eventQ::GetTop()
{
	event * theEvent = iQ.top();
//	iQ.pop();
	return theEvent;
}


int main(int argc, const char * argv[])
{

	// insert code here...
	cout << "Hello, Jack!" << endl;
	
	eventQ testQ; //define eventQ;

	event * testEvent;
	testEvent->time = 10;
	
//	cout << testEvent->time << endl;
	
	//You have to pass a pointer to an event. ITS ALL POINTERS!!
	testQ.Add(testEvent);
	cout << testQ.GetTop()->time << endl;
	
	//CHALLENGE.
	//Pull out the top() etc. EXPAND! GO GO GO!
	//To pull out the top() need a function in eventQ to get the top of the Q -> see Jeff's code

	
//	priority_queue<testClass, vector<testClass>, timeComparison> testQ;
	
//	yr_cd4 = {10,5};

    return 0;
}

