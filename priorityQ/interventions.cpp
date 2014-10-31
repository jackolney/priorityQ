//
//  interventions.cpp
//  priorityQ
//
//  Created by Jack Olney on 31/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "interventions.h"
#include "cascadeEvents.h"

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
	if(*p_Hbct || *p_Vct || *p_HbctPocCd4 || *p_Linkage || *p_PreOutreach || *p_ImprovedCare || *p_PocCd4 || *p_VctPocCd4 || *p_ArtOutreach || *p_ImmediateArt || *p_UniversalTestAndTreat || *p_Adherence || *p_ArtDropout) {
		if(thePerson->GetBirthDay() < 14610)
			new Interventions(thePerson,14610);
		else
			new Interventions(thePerson,thePerson->GetBirthDay());
	}
}

/////////////////////
/////////////////////

Interventions::Interventions(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Interventions scheduled for " << Time << " (year = " << Time / 365.25 << ")" << endl);
}

Interventions::~Interventions()
{}

bool Interventions::CheckValid()
{
	return pPerson->Alive();
}

void Interventions::Execute()
{
	
/////////////////////
	
	/* Hbct */
	if(*p_Hbct) {
			//Need to include scenarios
		new SeedHct(pPerson,14610); //2010
		new SeedHct(pPerson,16071); //2014
		new SeedHct(pPerson,17532); //2018
		new SeedHct(pPerson,18993); //2022
		new SeedHct(pPerson,20454); //2026
	
//	if(*p_Hbct == 1)
//			//dosomething;
//	else
//			//dosomethingelse;
			
	
	}
	
/////////////////////
	
	/* Vct */
	if(*p_Vct) {
		
	}
	
/////////////////////
	
	/* HbctPocCd4 */
	if(*p_HbctPocCd4) {
		
	}

/////////////////////
	
	/* Linkage */
	if(*p_Linkage) {
		
	}
	
/////////////////////
	
	/* PreOutreach */
	if(*p_PreOutreach) {
		
	}

/////////////////////

	/* ImprovedCare */
	if(*p_ImprovedCare) {
		
	}

/////////////////////
	
	/* PocCd4 */
	if(*p_PocCd4) {
		
	}
	
/////////////////////
	
	/* VctPocCd4 */
	if(*p_VctPocCd4) {
		
	}
	
/////////////////////
	
	/* ArtOutreach */
	if(*p_ArtOutreach) {
		
	}
	
/////////////////////
	
	/* ImmediateArt */
	if(*p_ImmediateArt) {
		
	}
	
/////////////////////
	
	/* UniversalTestAndTreat */
	if(*p_UniversalTestAndTreat) {
		
	}
	
/////////////////////
	
	/* Adherence */
	if(*p_Adherence) {
		
	}

/////////////////////
	
	/* ArtDropout */
	if(*p_ArtDropout) {
		
	}
	
/////////////////////
	
}
	
/////////////////////
/////////////////////