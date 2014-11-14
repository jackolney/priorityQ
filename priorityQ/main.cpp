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
#include "population.h"
#include "eventQ.h"
#include "output.h"

#include "person.h"
#include <algorithm>

using namespace std;

/* Pointers to core stuff */
Rng * theRng;
eventQ * theQ;

/* Intervention Pointers */
int const * p_Hbct;
int const * p_Vct;
int const * p_HbctPocCd4;
int const * p_Linkage;
int const * p_PreOutreach;
int const * p_ImprovedCare;
int const * p_PocCd4;
int const * p_VctPocCd4;
int const * p_ArtOutreach;
int const * p_ImmediateArt;
int const * p_UniversalTestAndTreat;
int const * p_Adherence;


double t(int i) {
	int r = theRng->doub() * 1000;
	return r % i;
}

void testFunction(int theSize, vector<person *> * theVector)
{
		//Setup output array values.
	unsigned long output[theSize];
	
	random_shuffle(theVector->begin(),theVector->end(),t);
	
	for(size_t i=0;i<theSize;i++) {
		output[i] = theVector->at(i)->GetPersonIndex();
		cout << output[i] << " = output[" << i << "]" << endl;
	}
	
}

int main(int argc, const char * argv[])
{
	/* Intervention Triggers (0 = OFF, 1 = ON (Best), 2 = ON (Realistic)) */
	int s_Hbct = 0;
	int s_Vct = 0;
	int s_HbctPocCd4 = 0;
	int s_Linkage = 0;
	int s_PreOutreach = 0;
	int s_ImprovedCare = 0;
	int s_PocCd4 = 0;
	int s_VctPocCd4 = 0;
	int s_ArtOutreach = 0;
	int s_ImmediateArt = 0;
	int s_UniversalTestAndTreat = 0;
	int s_Adherence = 0;
	
	p_Hbct = &s_Hbct;
	p_Vct = &s_Vct;
	p_HbctPocCd4 = &s_HbctPocCd4;
	p_Linkage = &s_Linkage;
	p_PreOutreach = &s_PreOutreach;
	p_ImprovedCare = &s_ImprovedCare;
	p_PocCd4 = &s_PocCd4;
	p_VctPocCd4 = &s_VctPocCd4;
	p_ArtOutreach = &s_ArtOutreach;
	p_ImmediateArt = &s_ImmediateArt;
	p_UniversalTestAndTreat = &s_UniversalTestAndTreat;
	p_Adherence = &s_Adherence;
	
	/* THE MODEL */
	theRng = new Rng(mach_absolute_time());

	theQ = new eventQ(0);
	
	population * thePop = new population(10);
	
//	theQ->RunEvents();

	person * aGuy = new person(thePop,1);
	person * aGirl = new person(thePop,1);
	person * bGuy = new person(thePop,1);
	person * bGirl = new person(thePop,1);
	person * cGuy = new person(thePop,1);
	person * cGirl = new person(thePop,1);
	person * dGuy = new person(thePop,1);
	person * dGirl = new person(thePop,1);
	

	cout << "people.at(0).size() = " << thePop->people.at(0).size() << endl;
	
	for(size_t i=0;i<thePop->people.at(0).size();i++)
		cout << thePop->people.at(0).at(i)->GetPersonIndex() << endl;
	
	testFunction(3, &thePop->people.at(0));
	
//	cout << testArray[9] << endl;
	
		//Pick random number in a range.
	
	
		//Pass vector with a pointer &testVector
	
		// So 'range' will be the size of the newInfections(s,a)
		// Then once Ive picked one... need to remove it and pick from the remainder.
	
		//Need a function that takes the size of the number of values to return, the vector row and then spits back the personIndex of the relevant people.
	
	
	
	delete theQ;
	delete theRng;

    return 0;
}
