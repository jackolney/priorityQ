//
//  calibration.cpp
//  priorityQ
//
//  Created by Jack Olney on 01/12/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "calibration.h"

using namespace std;

/* Calibration Pointers */
double * C1;
double * L21;
double * R3;
unsigned int * R3_Counter;
double * R8;
unsigned int * R8_Counter;
double * ART1;
double * ART4;
double * ART5;
double * ART6;
unsigned int * ART6_Counter;
double * ART9;
double * ART10;
unsigned int * ART10_Counter;
double * ART11;
double * ART12;
unsigned int * ART12_Counter;
double * ART13;
double * ART14;
double * pre2010;
unsigned int * HivArray;
unsigned int * ArtArray;

void SeedCalibration(person * const thePerson, const double theTimeZero, const double theTimeOne, const double theTimeTwo, const double theTimeThree)
{
	if(thePerson->GetBirthDay() < theTimeZero)
		new TimeSplitZero(thePerson,theTimeZero);
	
	if(thePerson->GetBirthDay() < theTimeOne)
		new TimeSplitOne(thePerson,theTimeOne);
	
	if(thePerson->GetBirthDay() < theTimeTwo)
		new TimeSplitTwo(thePerson,theTimeTwo);
	
	if(thePerson->GetBirthDay() < theTimeThree)
		new TimeSplitThree(thePerson,theTimeThree);
}

/////////////////////
/////////////////////

TimeSplitZero::TimeSplitZero(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitZero::~TimeSplitZero()
{}

bool TimeSplitZero::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitZero::Execute()
{
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

TimeSplitOne::TimeSplitOne(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitOne::~TimeSplitOne()
{}

bool TimeSplitOne::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitOne::Execute()
{
	UpdateCalibrationArrayOne(pPerson);
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

TimeSplitTwo::TimeSplitTwo(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitTwo::~TimeSplitTwo()
{}

bool TimeSplitTwo::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitTwo::Execute()
{
	UpdateCalibrationArrayTwo(pPerson);
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

TimeSplitThree::TimeSplitThree(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{}

TimeSplitThree::~TimeSplitThree()
{}

bool TimeSplitThree::CheckValid()
{
	return pPerson->Alive();
}

void TimeSplitThree::Execute()
{
	UpdateCalibrationArrayThree(pPerson);
	pPerson->ResetCalibration();
}

/////////////////////
/////////////////////

void CreateCalibrationArray()
{
	C1 = new double[9];
	L21 = new double[36];
	R3 = new double[9];
	R3_Counter = new unsigned int[9];
	R8 = new double[9];
	R8_Counter = new unsigned int[9];
	ART1 = new double[48];
	ART4 = new double[3];
	ART5 = new double[9];
	ART6 = new double[3];
	ART6_Counter = new unsigned int[3];
	ART9 = new double[9];
	ART10 = new double[3];
	ART10_Counter = new unsigned int[3];
	ART11 = new double[9];
	ART12 = new double[3];
	ART12_Counter = new unsigned int[3];
	ART13 = new double[9];
	ART14 = new double[9];
	pre2010 = new double[3];
	HivArray = new unsigned int[3];
	ArtArray = new unsigned int[3];
	
	for(size_t i=0;i<48;i++) {
		if(i<3) {
			ART4[i] = 0;
			ART6[i] = 0;
			ART6_Counter[i] = 0;
			ART10[i] = 0;
			ART10_Counter[i] = 0;
			ART12[i] = 0;
			ART12_Counter[i] = 0;
			pre2010[i] = 0;
			HivArray[i] = 0;
			ArtArray[i] = 0;
		}
		if(i<9) {
			C1[i] = 0;
			R3[i] = 0;
			R3_Counter[i] = 0;
			R8[i] = 0;
			R8_Counter[i] = 0;
			ART5[i] = 0;
			ART9[i] = 0;
			ART11[i] = 0;
			ART13[i] = 0;
			ART14[i] = 0;
		}
		if(i<36)
			L21[i] = 0;
		ART1[i] = 0;
	}
}

/////////////////////
/////////////////////

void UpdateCalibrationArrayOne(person * const thePerson)
{
	// C1 - Proportion of individuals that ever enter care.
	if(thePerson->GetCalEverDiag())
		C1[thePerson->GetCalDiagRoute()-1]++; //1 = Hct, 2 = Vct, 3 = Pict.
	
	// L2.1 - CD4 count at first CD4 measurement.
	if(thePerson->GetCalEverCare()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4EntryCare()) {
			case 1: i = 0; break;
			case 2: i = 1; break;
			case 3: i = 2; break;
			case 4: i = 3; break;
			default: i = 0;
		}
		i += (thePerson->GetCalDiagRoute()-1) * 4;
		L21[i]++;
	}

	// R3 - Mean number of secondary CD4 appointments prior to becoming eligible for ART.
	if(thePerson->GetCalEverArt()) {
		R3[thePerson->GetCalAtArtDiagRoute()-1] += thePerson->GetCalSecondaryCd4TestCount();
		R3_Counter[thePerson->GetCalAtArtDiagRoute()-1]++;
	}
	
	// R8 - Mean CD4 count when receiving secondary CD4 test results.
	if(thePerson->GetCalEverCare()) {
		R8[thePerson->GetCalDiagRoute()-1] += thePerson->GetCalCd4SecondaryCd4Test();
		R8_Counter[thePerson->GetCalDiagRoute()-1]++;
	}
	
	// ART1 - CD4 count at ART initiation.
	if(thePerson->GetCalEverArt()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4AtArt()) {
			case 1: i = 0; break;
			case 2: i = 1; break;
			case 3: i = 2; break;
			case 4: i = 3; break;
			default: i = 0;
		}
		i += (thePerson->GetCalAtArtDiagRoute()-1) * 4;
		ART1[i]++;
	}
	
	// ART4 - Mean number of pre-ART clinic visits prior to ART initiation.
	if(thePerson->GetCalEverArt())
		ART4[0] += thePerson->GetCalAtArtPreArtVisitCount();
	
	// ART5 - Proportion of ppl initiating ART after diagnosis and successful retention in care until becoming eligible for treatment.
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverLostCare())
		ART5[thePerson->GetCalAtArtDiagRoute()-1]++;

	// ART6 - Mean time from diagnosis to ART initiation for ppl successfully retained in care. (HCT ONLY)
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverLostCare()) {
		ART6[0] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART6_Counter[0]++;
	}
	
	// ART9 - Proportion of ppl initiating ART, loss but return prior to becoming eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare())
		ART9[thePerson->GetCalAtArtDiagRoute()-1]++;
	
	// ART10 - Mean time from diagnosis to ART initiation for ppl lost but returned prior to becoming eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART10[0] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART10_Counter[0]++;
	}
	
	// ART11 - Proportion of ppl initiating ART, loss andd return when eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare())
		ART11[thePerson->GetCalAtArtDiagRoute()-1]++;
	
	
	// ART12 - Mean time from diagnosis to ART initiation for ppl lost and returned when eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART12[0] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART12_Counter[0]++;
	}

	// ART13 - Proportion of ppl initiating ART who had already been on it.
	if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
		ART13[thePerson->GetCalAtArtDiagRoute()-1]++;
	
	// ART14 - Proportion of ppl initiating ART at enrollment visit (FastTrackArt).
	if(thePerson->GetCalEverArt() && thePerson->GetCalArtAtEnrollment())
		ART14[thePerson->GetCalAtArtDiagRoute()-1]++;
	
	// HIV-positive individuals initiating ART per year;
	if(thePerson->GetSeroStatus())
		HivArray[0]++;
	if(thePerson->GetArtInitiationState())
		ArtArray[0]++;
	
	// pre2010 - Dx levels pre-2010. (don't run this code after 2010)
	if(thePerson->GetCalEverCare()) {
		pre2010[0]++;
		if(thePerson->GetCalDiagRoute() == 2)
			pre2010[1]++;
		else if(thePerson->GetCalDiagRoute() == 3)
			pre2010[2]++;
	}
	
}

/////////////////////
/////////////////////

void UpdateCalibrationArrayTwo(person * const thePerson)
{
	// C1 - Proportion of individuals that ever enter care.
	if(thePerson->GetCalEverDiag())
		C1[3 + (thePerson->GetCalDiagRoute()-1)]++; //1 = Hct, 2 = Vct, 3 = Pict.
	
	// L2.1 - CD4 count at first CD4 measurement.
	if(thePerson->GetCalEverCare()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4EntryCare()) {
			case 1: i = 0; break;
			case 2: i = 1; break;
			case 3: i = 2; break;
			case 4: i = 3; break;
			default: i = 0;
		}
		i += (thePerson->GetCalDiagRoute()-1) * 4;
		L21[12 + i]++;
	}
	
	// R3 - Mean number of secondary CD4 appointments prior to becoming eligible for ART.
	if(thePerson->GetCalEverArt()) {
		R3[3 + (thePerson->GetCalAtArtDiagRoute()-1)] += thePerson->GetCalSecondaryCd4TestCount();
		R3_Counter[3 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	}
	
	// R8 - Mean CD4 count when receiving secondary CD4 test results.
	if(thePerson->GetCalEverCare()) {
		R8[3 + (thePerson->GetCalDiagRoute()-1)] += thePerson->GetCalCd4SecondaryCd4Test();
		R8_Counter[3 + (thePerson->GetCalDiagRoute()-1)]++;
	}
	
	// ART1 - CD4 count at ART initiation.
	if(thePerson->GetCalEverArt()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4AtArt()) {
			case 1: i = 0; break;
			case 2: i = 1; break;
			case 3: i = 2; break;
			case 4: i = 3; break;
			default: i = 0;
		}
		i += (thePerson->GetCalAtArtDiagRoute()-1) * 4;
		ART1[16 + i]++;
	}
	
	// ART4 - Mean number of pre-ART clinic visits prior to ART initiation.
	if(thePerson->GetCalEverArt())
		ART4[1] += thePerson->GetCalAtArtPreArtVisitCount();
	
	// ART5 - Proportion of ppl initiating ART after diagnosis and successful retention in care until becoming eligible for treatment.
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverLostCare())
		ART5[3 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// ART6 - Mean time from diagnosis to ART initiation for ppl successfully retained in care. (HCT ONLY)
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverLostCare()) {
		ART6[1] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART6_Counter[1]++;
	}
	
	// ART9 - Proportion of ppl initiating ART, loss but return prior to becoming eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare())
		ART9[3 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// ART10 - Mean time from diagnosis to ART initiation for ppl lost but returned prior to becoming eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART10[1] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART10_Counter[1]++;
	}
	
	// ART11 - Proportion of ppl initiating ART, loss andd return when eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare())
		ART11[3 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	
	// ART12 - Mean time from diagnosis to ART initiation for ppl lost and returned when eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART12[1] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART12_Counter[1]++;
	}
	
	// ART13 - Proportion of ppl initiating ART who had already been on it.
	if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
		ART13[3 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// ART14 - Proportion of ppl initiating ART at enrollment visit (FastTrackArt).
	if(thePerson->GetCalEverArt() && thePerson->GetCalArtAtEnrollment())
		ART14[3 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// HIV-positive individuals initiating ART per year;
	if(thePerson->GetSeroStatus())
		HivArray[1]++;
	if(thePerson->GetArtInitiationState())
		ArtArray[1]++;
}

/////////////////////
/////////////////////

void UpdateCalibrationArrayThree(person * const thePerson)
{
	// C1 - Proportion of individuals that ever enter care.
	if(thePerson->GetCalEverDiag())
		C1[6 + (thePerson->GetCalDiagRoute()-1)]++; //1 = Hct, 2 = Vct, 3 = Pict.
	
	// L2.1 - CD4 count at first CD4 measurement.
	if(thePerson->GetCalEverCare()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4EntryCare()) {
			case 1: i = 0; break;
			case 2: i = 1; break;
			case 3: i = 2; break;
			case 4: i = 3; break;
			default: i = 0;
		}
		i += (thePerson->GetCalDiagRoute()-1) * 4;
		L21[24 + i]++;
	}
	
	// R3 - Mean number of secondary CD4 appointments prior to becoming eligible for ART.
	if(thePerson->GetCalEverArt()) {
		R3[6 + (thePerson->GetCalAtArtDiagRoute()-1)] += thePerson->GetCalSecondaryCd4TestCount();
		R3_Counter[6 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	}
	
	// R8 - Mean CD4 count when receiving secondary CD4 test results.
	if(thePerson->GetCalEverCare()) {
		R8[6 + (thePerson->GetCalDiagRoute()-1)] += thePerson->GetCalCd4SecondaryCd4Test();
		R8_Counter[6 + (thePerson->GetCalDiagRoute()-1)]++;
	}
	
	// ART1 - CD4 count at ART initiation.
	if(thePerson->GetCalEverArt()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4AtArt()) {
			case 1: i = 0; break;
			case 2: i = 1; break;
			case 3: i = 2; break;
			case 4: i = 3; break;
			default: i = 0;
		}
		i += (thePerson->GetCalAtArtDiagRoute()-1) * 4;
		ART1[32 + i]++;
	}
	
	// ART4 - Mean number of pre-ART clinic visits prior to ART initiation.
	if(thePerson->GetCalEverArt())
		ART4[2] += thePerson->GetCalAtArtPreArtVisitCount();
	
	// ART5 - Proportion of ppl initiating ART after diagnosis and successful retention in care until becoming eligible for treatment.
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverLostCare())
		ART5[6 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// ART6 - Mean time from diagnosis to ART initiation for ppl successfully retained in care. (HCT ONLY)
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverLostCare()) {
		ART6[2] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART6_Counter[2]++;
	}
	
	// ART9 - Proportion of ppl initiating ART, loss but return prior to becoming eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare())
		ART9[6 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// ART10 - Mean time from diagnosis to ART initiation for ppl lost but returned prior to becoming eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART10[2] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART10_Counter[2]++;
	}
	
	// ART11 - Proportion of ppl initiating ART, loss andd return when eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare())
		ART11[6 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	
	// ART12 - Mean time from diagnosis to ART initiation for ppl lost and returned when eligible.
	if(thePerson->GetCalEverArt() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART12[2] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART12_Counter[2]++;
	}
	
	// ART13 - Proportion of ppl initiating ART who had already been on it.
	if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
		ART13[6 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// ART14 - Proportion of ppl initiating ART at enrollment visit (FastTrackArt).
	if(thePerson->GetCalEverArt() && thePerson->GetCalArtAtEnrollment())
		ART14[6 + (thePerson->GetCalAtArtDiagRoute()-1)]++;
	
	// HIV-positive individuals initiating ART per year;
	if(thePerson->GetSeroStatus())
		HivArray[2]++;
	if(thePerson->GetArtInitiationState())
		ArtArray[2]++;
}

/////////////////////
/////////////////////