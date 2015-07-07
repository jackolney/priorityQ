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
population * thePop;

/* Output */
extern double * thePOP_15to49;
extern double * theHIV_15to49;
extern double * thePOP;
extern double * theHIV;
extern double * theART_15to49;
extern double * theINCIDENCE;

extern double * theDALY;
extern double * theCOST;
extern double * thePreArtCOST;
extern double * theArtCOST;
extern double * thePreArtCOST_Hiv;
extern double * theArtCOST_Hiv;
extern double * theCLINIC;

extern int * theGuidelines_PopDist_HivNegative;
extern int * theGuidelines_Death_200_ArtMoreSixMonths;
extern int * theGuidelines_Death_200_OffArt;
extern int * theGuidelines_Art_500;
extern int * theGuidelines_NewInfectionsAdult;
extern int * theGuidelines_NewDiagnoses;
extern int * theGuidelines_PreArtDropout;
extern int * theGuidelines_ArtDropout;

/* Intervention Pointers */
int const * p_NaiveHbct;
int const * p_HbctNcd;
int const * p_HbctNcdPreArtRetention;
int const * p_HbctNcdRetention;
int const * p_HbctNcdRetentionAdherence;
int const * p_HbctFrequency;
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
int const * p_Calibration;

/* Calibration pointers */
extern double * L21;

int main(int argc, const char * argv[])
{
	/* Intervention Triggers (0 = OFF, 1 = ON (Best), 2 = ON (Realistic)) */
	int s_NaiveHbct = 0;
	int s_HbctNcd = 0;
	int s_HbctNcdPreArtRetention = 0;
	int s_HbctNcdRetention = 0;
	int s_HbctNcdRetentionAdherence = 0;
	int s_HbctFrequency = 0;
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
	int s_Calibration = 0;

	p_NaiveHbct = &s_NaiveHbct;
	p_HbctNcd = &s_HbctNcd;
	p_HbctNcdPreArtRetention = &s_HbctNcdPreArtRetention;
	p_HbctNcdRetention = &s_HbctNcdRetention;
	p_HbctNcdRetentionAdherence = &s_HbctNcdRetentionAdherence;
	p_HbctFrequency = &s_HbctFrequency;
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
	p_Calibration = &s_Calibration;
	

	for(size_t runNumber=0;runNumber<1;runNumber++) {
		
		/* THE MODEL */
		theRng = new Rng(mach_absolute_time());

		theQ = new eventQ(0,(66 * 365.25) + 1);
		
		const int SizeAdjustment = 1000;
		
		new population(SizeAdjustment);
		
		theQ->RunEvents();
		
		/* PLAYGROUND */
		
//		cout << "hello" << endl;
//		
//		double theTime = 2004;
//		
//		if(theTime >= 2000) {
//			double yr [36];
//			for(size_t i=0; i<36; i++)
//				yr[i] = 2001 + i;
//			
//			unsigned int i=0;
//			while(theTime >= yr[i] && i<36)
//				i++;
//			
//			cout << "i = " << i << endl;
//		}
		
		cout << "theDALY:" << endl;
		for(size_t i=0; i<20; i++)
			cout << theDALY[i] << endl;
		
//		cout << "theGuidelines_Death_200_OffArt:" << endl;
//		for(size_t i=0; i<36; i++)
//			cout << theGuidelines_Death_200_OffArt[i] << endl;
//		
//		cout << "theGuidelines_Art_500:" << endl;
//		for(size_t i=0; i<36; i++)
//			cout << theGuidelines_Art_500[i] << endl;
//		
//		cout << "theGuidelines_NewInfectionsAdult:" << endl;
//		for(size_t i=0; i<36; i++)
//			cout << theGuidelines_NewInfectionsAdult[i] << endl;
//		
//		cout << "theGuidelines_NewDiagnoses:" << endl;
//		for(size_t i=0; i<36; i++)
//			cout << theGuidelines_NewDiagnoses[i] << endl;
//		
//		cout << "theGuidelines_PreArtDropout:" << endl;
//		for(size_t i=0; i<36; i++)
//			cout << theGuidelines_PreArtDropout[i] << endl;
//		
//		cout << "theGuidelines_ArtDropout:" << endl;
//		for(size_t i=0; i<36; i++)
//			cout << theGuidelines_ArtDropout[i] << endl;
		
		delete theQ;
		delete theRng;
		delete thePop;
		
	}

    return 0;
}
