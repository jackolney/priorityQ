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
#include "interventionUpdate.h"
#include "interventionEvents.h"
#include "cascadeEvents.h"
#include "cascadeUpdate.h"
#include "toolbox.h"
#include "eventQ.h"

using namespace std;

extern eventQ * theQ;

/* Intervention Pointers */
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

/////////////////////
/////////////////////

void SeedInterventions(person * const thePerson)
{
	if(*p_Hbct || *p_Vct || *p_HbctPocCd4 || *p_Linkage || *p_PreOutreach || *p_ImprovedCare || *p_PocCd4 || *p_VctPocCd4 || *p_ArtOutreach || *p_ImmediateArt || *p_UniversalTestAndTreat || *p_Adherence) {
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
/////////////////////
	/* Hbct */
	
	if(*p_Hbct) {
		for(size_t i=0;i<5;i++)
			if(GetTime() <= 14610 + (i * 1461))
				new SeedHct(pPerson,14610 + (i * 1461),false);
		
		if(*p_Hbct == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
		}
	}
	
/////////////////////
	/* Vct */
	
	if(*p_Vct) {
		if(*p_Vct == 1)
			vctHivTestTime = 2.9 * 365.25;
		else
			vctHivTestTime = 4.64 * 365.25;
		D(cout << "VctHivTest Intervention. vctHivTestTime = " << vctHivTestTime << endl);
		ScheduleVctHivTest(pPerson);
	}
	
/////////////////////
	/* HbctPocCd4 */
	
	if(*p_HbctPocCd4) {
		D(cout << "HbctPocCd4 Intervention." << endl);
		for(size_t i=0;i<5;i++)
			if(GetTime() <= 14610 + (i * 1461))
				new SeedHct(pPerson,14610 + (i * 1461),true);
		
		if(*p_HbctPocCd4 == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
		} else {
			hctProbLink = 0.527;
			hctProbLinkPreviouslyDiagnosed = 0.6;
		}
	}

/////////////////////
	/* Linkage */
	
	if(*p_Linkage) {
		D(cout << "Linkage intervention." << endl);
		if(*p_Linkage == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
			vctProbLink = 1;
			pictProbLink = 1;
		} else {
			hctProbLink = 0.527;
			hctProbLinkPreviouslyDiagnosed = 0.6;
			vctProbLink = 0.795;
			pictProbLink = 0.77;
		}
	}
	
/////////////////////
	/* PreOutreach */
	
	if(*p_PreOutreach) {
		double k = 0;
		if(*p_PreOutreach == 1) { k = 1; } else { k = 0.2; }
		
		for(size_t i=0;i<20;i++)
			if(GetTime() <= 14792.625 + (i * 365.25))
				new PreArtOutreach(pPerson,14792.625 + (i * 365.25),k);
	}

/////////////////////
	/* ImprovedCare */
	
	if(*p_ImprovedCare) {
		D(cout << "ImprovedCare intervention." << endl);
		if(*p_ImprovedCare == 1) {
			cd4ResultProbAttend = 1;
			hctShortTermRetention = 1;
			hctLongTermRetention = 1;
			vctShortTermRetention = 1;
			vctLongTermRetention = 1;
			pictShortTermRetention = 1;
			pictLongTermRetention = 1;
			hctProbSecondaryCd4Test = 1;
			vctProbSecondaryCd4Test = 1;
			pictProbSecondaryCd4Test = 1;
		} else {
			cd4ResultProbAttend = 0.9;
			hctShortTermRetention = 0.8096;
			hctLongTermRetention = 0.8096;
			vctShortTermRetention = 0.7663;
			vctLongTermRetention = 0.7663;
			pictShortTermRetention = 0.77035;
			pictLongTermRetention = 0.77035;
			hctProbSecondaryCd4Test = 0.71665;
			vctProbSecondaryCd4Test = 0.65525;
			pictProbSecondaryCd4Test = 0.65645;
		}
	}

/////////////////////
	/* PocCd4 */
	
	if(*p_PocCd4)
		pocFlag = true;
	
/////////////////////
	/* VctPocCd4 */
	
	if(*p_VctPocCd4)
		vctPocFlag = true;
	
/////////////////////
	/* ArtOutreach */
	
	if(*p_ArtOutreach) {
		double k = 0;
		if(*p_ArtOutreach == 1) { k = 1; } else { k = 0.4; }
		
		for(size_t i=0;i<20;i++)
			if(GetTime() <= 14792.625 + (i * 365.25))
				new ArtOutreach(pPerson,14792.625 + (i * 365.25),k);
	}
	
/////////////////////
	/* ImmediateArt */
	
	if(*p_ImmediateArt) {
		D(cout << "ImmediateArt intervention." << endl);
		immediateArtFlag = true;
		UpdateTreatmentGuidelines(pPerson,4,1);
	}
	
/////////////////////
	/* UniversalTestAndTreat */
	
	if(*p_UniversalTestAndTreat) {
		D(cout << "UniversalTestAndTreat intervention." << endl);
		immediateArtFlag = true;
		UpdateTreatmentGuidelines(pPerson,4,1);
		
		if(*p_UniversalTestAndTreat == 1)
			universalTestAndTreatFlag = 1;
		else
			universalTestAndTreatFlag = 2;
		
		for(size_t i=0;i<5;i++)
			if(GetTime() <= 14610 + (i * 1461))
				new SeedHct(pPerson,14610 + (i * 1461),false);
	}
	
/////////////////////
	/* Adherence */
	
	if(*p_Adherence) {
		D(cout << "Adherence intervention." << endl);
		adherenceFlag = true;
		if(*p_Adherence == 1)
			pPerson->SetArtAdherenceState(1);
		else
			pPerson->SetArtAdherenceState(0.875);
	}
	
/////////////////////
	
}

/////////////////////
/////////////////////
