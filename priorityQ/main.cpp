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
#include "toolbox.h"

using namespace std;

/* Pointers to core stuff */
Rng * theRng;
eventQ * theQ;

/* Output */
extern double * thePOP_15to49;
extern double * theHIV_15to49;
extern double * thePOP;
extern double * theHIV;
extern double * theART_15to49;
extern double * theINCIDENCE;

extern double * theCOST;
extern double * thePreArtCOST;
extern double * theArtCOST;

/* Intervention Pointers */
int const * p_Hbct;
int const * p_Vct;
int const * p_HbctPocCd4;
int const * p_Linkage;
int const * p_VctPocCd4;
int const * p_PreOutreach;
int const * p_ImprovedCare;
int const * p_PocCd4;
int const * p_ArtOutreach;
int const * p_Adherence;
int const * p_ImmediateArt;
int const * p_UniversalTestAndTreat;

int main(int argc, const char * argv[])
{
	/* Intervention Triggers (0 = OFF, 1 = ON (Best), 2 = ON (Realistic)) */
	int s_Hbct = 0;
	int s_Vct = 0;
	int s_HbctPocCd4 = 0;
	int s_Linkage = 0;
	int s_VctPocCd4 = 0;
	int s_PreOutreach = 0;
	int s_ImprovedCare = 0;
	int s_PocCd4 = 0;
	int s_ArtOutreach = 0;
	int s_Adherence = 0;
	int s_ImmediateArt = 0;
	int s_UniversalTestAndTreat = 0;

	p_Hbct = &s_Hbct;
	p_Vct = &s_Vct;
	p_HbctPocCd4 = &s_HbctPocCd4;
	p_Linkage = &s_Linkage;
	p_VctPocCd4 = &s_VctPocCd4;
	p_PreOutreach = &s_PreOutreach;
	p_ImprovedCare = &s_ImprovedCare;
	p_PocCd4 = &s_PocCd4;
	p_ArtOutreach = &s_ArtOutreach;
	p_Adherence = &s_Adherence;
	p_ImmediateArt = &s_ImmediateArt;
	p_UniversalTestAndTreat = &s_UniversalTestAndTreat;
	
	/* THE MODEL */
	theRng = new Rng(mach_absolute_time());

	theQ = new eventQ(0,61*365.25);
	
	new population(1000);
	
	theQ->RunEvents();
	
	cout << "Pop15to49:" << endl;
	for(size_t i=0;i<60;i++)
		cout << thePOP_15to49[i] << endl;
	
	cout << endl;
	
	cout << "HIV15to49:" << endl;
	for(size_t i=0;i<60;i++)
		cout << theHIV_15to49[i] << endl;

	cout << endl;
	
	cout << "Art15to49:" << endl;
	for(size_t i=0;i<60;i++)
		cout << theART_15to49[i] << endl;
	
	cout << endl;
	
	cout << "Incidence:" << endl;
	for(size_t i=0;i<60;i++)
		cout << theINCIDENCE[i] << endl;
	
	cout << endl;
	
	cout << "COST:" << endl;
	for(size_t i=0;i<20;i++)
		cout << theCOST[i] << endl;
	
	cout << "PreArtCOST:" << endl;
	for(size_t i=0;i<20;i++)
		cout << thePreArtCOST[i] << endl;
	
	cout << "ARTCOST:" << endl;
	for(size_t i=0;i<20;i++)
		cout << theArtCOST[i] << endl;
	
	delete theQ;
	delete theRng;

    return 0;
}
