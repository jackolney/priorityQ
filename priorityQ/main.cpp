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
	
	person * thePerson = new person(thePop,1);
	person * theOtherPerson = new person(thePop,1);
	person * yetAnotherPerson = new person(thePop,1);
	
	thePop->SwapOut(theOtherPerson);
	
//	cout << thePerson->GetPersonIndex() << endl;
//	cout << theOtherPerson->GetPersonIndex() << endl;
//	cout << yetAnotherPerson->GetPersonIndex() << endl;
//	cout << thePerson->GetNatDeathDate() << endl;
//	cout << theOtherPerson->GetNatDeathDate() << endl;
//	cout << yetAnotherPerson->GetNatDeathDate() << endl;
//	
//	cout << endl;
//	cout << thePop->Susceptible.at(0).size() << endl;
//	cout << endl;
//	
//		//Attempt a swap of theOtherPerson;
//	cout << theOtherPerson->GetPersonIndex() << endl;
//	cout << thePop->Susceptible.at(0)[theOtherPerson->GetPersonIndex()]->GetNatDeathDate() << endl;
//	
//	
//		//THE POP BACK.
//		//	thePop->Susceptible.at(0).pop_back();
//		//	thePop->Susceptible.at(0).pop_back();
//	cout << thePop->Susceptible.at(0).empty() << " = empty." << endl;
//	cout << endl;
//	
//		//THE SWITCH.
//		// Steps:
//		// 1. Replace otherPerson with anotherPerson;
//		// 2. pop_back();
//		// 3. Bro down?
//	thePop->Susceptible.at(0).at(theOtherPerson->GetPersonIndex()) = yetAnotherPerson;
//	yetAnotherPerson->SetPersonIndex(theOtherPerson->GetPersonIndex());
//	thePop->Susceptible.at(0).pop_back();
//	cout << thePop->Susceptible.at(0).size() << endl;
//	cout << thePop->Susceptible.at(0).at(yetAnotherPerson->GetPersonIndex())->GetNatDeathDate() << endl;

	
	
	
			//	cout << thePop->Susceptible.at(0).size() << endl;
			//	thePop->Susceptible.at(0).push_back(theGuy);
			//	cout << thePop->Susceptible.at(0).size() << endl;
				
			//	cout << thePop->Susceptible[0].size() << endl;
				
			//	cout << thePop->Susceptible.at(0)->push_back(theGuy) << endl;
	
			//	int num_of_col = 5;
			//	int num_of_row = 9;
			//	double init_value = 10;
			//	
			//	vector< vector<double> > matrix;
			//		//now we have an empty 2D-matrix of size (0,0). Resizing it with one single command:
			//	matrix.resize( num_of_col , vector<double>( num_of_row , init_value ) );
			//		// and we are good to go ...
			//	cout << matrix.size() << endl;
			//	cout << matrix.at(0).size() << endl;
			//	matrix.at(0).push_back(1);
			//	cout << matrix.at(0).size() << endl;
			//	matrix.at(0).erase(matrix.at(0).begin());
			//	cout << matrix.at(0).size() << endl;
			//	cout << matrix[0][0] << endl;

//	theQ->RunEvents();
	
	delete theQ;
	delete theRng;

    return 0;
}
