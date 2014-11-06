	//
	//  outputUpdate.cpp
	//  priorityQ
	//
	//  Created by Jack Olney on 30/10/2014.
	//  Copyright (c) 2014 Jack Olney. All rights reserved.
	//

#include <iostream>
#include "outputUpdate.h"
#include "eventQ.h"

using namespace std;

extern eventQ * theQ;

extern double * thePOP;
extern double * theHIV;
extern double * theART;

/////////////////////
/////////////////////

void WritePop(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 60)
		i++;
	
	if(theQ->GetTime() > thePerson->GetBirthDay())
		thePOP[i] += thePerson->Alive();
}

/////////////////////
/////////////////////

void WriteHiv(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 60)
		i++;
	
	if(thePerson->Alive())
		theHIV[i] += thePerson->GetSeroStatus();
}

/////////////////////
/////////////////////

void WriteArt(person * const thePerson)
{
	double yr [60];
	for(size_t i = 0; i<60; i++)
		yr[i] = 365.25 + (i * 365.25);
	
	unsigned int i = 0;
	while(theQ->GetTime() > yr[i] && i < 60)
		i++;
	
	if(thePerson->Alive())
		theART[i] += thePerson->GetArtInitiationState();
}

/////////////////////
/////////////////////
