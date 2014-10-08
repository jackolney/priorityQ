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
			event(const double Time);	//Constructer [not neccessary at the moment]
//			~event();	//Destructer  [not neccessary at the moment]
	
//		double time = 0; //define time - make private eventually.
		void (*ptr_fun)(); //function pointer - make private eventually.
	
		/*Accessor methods*/
		double GetTime() const {return eventTime;}
		// Include a "GetTime()" when private.
		// Include a "GetFun()" when private.
	protected:
		const double eventTime;
	
};

event::event(const double Time) : eventTime(Time)
{}


	/*Define operator() for comparison class*/
struct timeComparison {
	bool operator()(const event *lhs, const event *rhs) const
	{
		return lhs->GetTime() > rhs->GetTime();
	}
};

	/*Define eventQ class*/
class eventQ {
	public:
	//	eventQ(); //need to initialise currentTime;
	//	~eventQ();
		
		/*Methods*/
		void AddEvent(event * const theEvent);
		//Jeff has a Run() here that walks through events.
		
		/*Accessor methods*/
		size_t Size() const; //size_t is a type able to represent the size of any object in bytes.
		//Empty
		double GetTime() const {return currentTime;}
	
		/*Methods*/
		event * GetTop(); //Perhaps make private eventually.
		void PopTop();
	
	private:
		priority_queue<event*, vector<event*>, timeComparison> iQ;
		double currentTime = 0; //assign in constructor Jack, don't get sloppy.
		//Can include a currentTime - perhaps not in here though.
	
};

	/*Define AddEvent()*/
void eventQ::AddEvent(event * const theEvent)
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

	/*Define PopTop()*/
void eventQ::PopTop()
{
	iQ.pop();
}

	/*Define Size()*/
size_t eventQ::Size() const //const after a function declaration means the function is not allowed to change any class members.
{
	return iQ.size();
}

	/*Test Function to be pointed to*/
void testFunc() {
	cout << "Hello, Jack. This function worked, aren't you clever." << endl;
}


int main(int argc, const char * argv[])
{

	/*Print Hello*/
	cout << "Hello, Jack!" << endl;
	
	/*Define the event queue*/
	eventQ testQ;

	/*Create event and provide time to constructor*/
	event * testEvent1 = new event(20); //Needs to be created on the heap so that (a) I can assign a time to the constructor and (b) allows me to destroy it later.
	event * testEvent2 = new event(5);
	
	testEvent1->ptr_fun = &testFunc;
	testEvent2->ptr_fun = &testFunc;
	
	/*Access time*/
	cout << testEvent1->GetTime() << endl;
	cout << testEvent2->GetTime() << endl;
	
	/*Add event to the Q*/
	testQ.AddEvent(testEvent1);
	testQ.AddEvent(testEvent2);
	
	/*Access top of the queue*/
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
	// 4) Transition to multiple cpp files.
	// 5) Including a "currentTime" we walk through time and execute the top of the queue, pop it off and continue.
	// 6) EXPAND to include all functions of the model.

    return 0;
}


/*NOTES*/

// Will create this model for one individual
// Transistion into defining an array of pointers (of class event) to an array of pointers (of class event Q) to corresponding eventQ's. Therefore allowing me to simulate mulitple individuals simultaneously.
