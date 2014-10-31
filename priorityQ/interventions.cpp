//
//  interventions.cpp
//  priorityQ
//
//  Created by Jack Olney on 31/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "interventions.h"

using namespace std;

extern int const * p_Hbct;
extern int const * p_Vct;
extern int const * p_HbctPocCd4;
extern int const * p_Linkage;
extern int const * p_PreOutreach;
extern int const * p_ImprovedCare;
extern int const * p_PocCd4;
extern int const * p_VctPocCd4;
extern int const * p_ArtOutreach;
extern int const * p_ImmediateArt;
extern int const * p_UniversalTestAndTreat;
extern int const * p_Adherence;
extern int const * p_ArtDropout;

/////////////////////
/////////////////////

void SeedInterventions(person * const thePerson)
{
	cout << *p_Hbct << " = s_Hbct." << endl;
	
	if(thePerson->GetBirthDay() < 14610)
		new Interventions(thePerson,14610);
	else
		new Interventions(thePerson,thePerson->GetBirthDay());
}

/////////////////////
/////////////////////

Interventions::Interventions(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

Interventions::~Interventions()
{}

bool Interventions::CheckValid()
{
return true;
}

void Interventions::Execute()
{
	//DoFunStuff()
}
	
/////////////////////
/////////////////////