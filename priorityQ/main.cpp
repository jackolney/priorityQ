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
	
	void Add(event * const theEvent);
	
	priority_queue<event*, vector<event*>, timeComparison> iQ;
	//Can include a currentTime;
	
};

void eventQ::Add(event * const theEvent)
{
	iQ.push(theEvent);
	
	return;
}

int main(int argc, const char * argv[])
{

	// insert code here...
	cout << "Hello, Jack!" << endl;
	
	eventQ testQ; //define eventQ;

	event * testEvent;
	testEvent->time = 10;
	
	cout << testEvent->time << endl;
	
	//You have to pass a pointer to an event. ITS ALL POINTERS!!
	testQ.Add(testEvent);
	

	
//	priority_queue<testClass, vector<testClass>, timeComparison> testQ;
	



    return 0;
}

