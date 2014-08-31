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

class testClass {
public:
	//	testClass();	//Constructer [not neccessary at the moment]
	//	~testClass();	//Destructer  [not neccessary at the moment]
	
	double time = 0;
	void (*p_fun)();
	
};

struct timeComparison {
	bool operator()(const testClass& lhs, const testClass& rhs) const
	{
		return lhs.time > rhs.time;
	}
};

double getTopTime(priority_queue<testClass, vector<testClass>, timeComparison> Q) {
	testClass result; // DO IT INLINE!
	result = Q.top();
	return result.time;
}

void getTopFun(priority_queue<testClass, vector<testClass>, timeComparison> Q) {
	testClass result;
	result = Q.top();
	result.p_fun();
}

void testPush(double time,void (*fun)(),priority_queue<testClass, vector<testClass>, timeComparison>& Q) {
	testClass eventTime;
	eventTime.time = time;
	eventTime.p_fun = fun;
	Q.push(eventTime);
}

void f() {printf("hello, this is function f.\n");};
void g() {printf("hello, this is function g.\n");};

int main(int argc, const char * argv[])
{

	// insert code here...
	cout << "Hello, Jack!" << endl;

	
	priority_queue<testClass, vector<testClass>, timeComparison> testQ;
	
/*Notes*/
	//The "event" class created in the getTop and push functions should be pointers to events! We are not copying anything, we just want pointers. MUCH NEATER!
	//Also follow proper naming rules: Variable = somethingThatIsAVariable, Function = DoFunStuff() [functions start with a capital]
	
	


	//Function to create a class, include a time and push it to the specified priority_queue.
	testPush(10,&f,testQ);
	testPush(25,&g,testQ);
	testPush(30,&f,testQ);
	
	cout << getTopTime(testQ) << " = is this the top of the testQ?" << endl;
	getTopFun(testQ);
	testQ.pop();
	cout << getTopTime(testQ) << " = is this the top of the testQ?" << endl;
	getTopFun(testQ);
	
	//////////
	/*I should be using pointers not copying classes from testQ.top()*/
	//////////
	/*create pointer of class 'testClass'*/
	testClass *ptr_test;
	
	/*create object we want the pointer to point to*/
	testClass example;
	
	/*point pointer to address of object we want it to point to*/
	ptr_test = &example;
	
	/*assign value to object*/
	example.time = 10;
	
	/*access value assigned to object through pointer*/
	cout << ptr_test->time << endl;
	///////////
	
	//Next challenge... be able to call a function from a priority_queue output...
	//Could I just use a pointer to a function?
	//i.e.
	//	void (*p_fun)();
	//	p_fun();
	//The pointer than accesses the specific function and does what it needs to...
	//Need to think how arguements are going to work here.
	
	//Next challenge: passing different arguements in each call to the function?
	//Hint: use void* [this is a void pointer]
	//Next: use varying numbers of arguments in a function, I think this uses an elipsis.
	
	cout << testQ.size() << " = size of the testQ" << endl;

	while(testQ.size() != 0) {
		testQ.pop();
	}


    return 0;
}

