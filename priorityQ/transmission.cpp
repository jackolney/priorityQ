//
//  transmission.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "transmission.h"
#include "incidence.h"

using namespace std;

extern Incidence * theInc;

/////////////////////
/////////////////////

Transmission::Transmission() :
referenceYear(11688),
beta(0)
{}

Transmission::~Transmission()
{}

void Transmission::UpdateVector(person * const thePerson)
{
	RemoveFromVector(thePerson);
	PushToVector(thePerson);
	
	D(cout << "pPersonCounter_Art.size() = " << pPersonCounter_Art.size() << endl);
	D(cout << "pPersonCounter_Cd4_4.size() = " << pPersonCounter_Cd4_4.size() << endl);
	D(cout << "pPersonCounter_Cd4_3.size() = " << pPersonCounter_Cd4_3.size() << endl);
	D(cout << "pPersonCounter_Cd4_2.size() = " << pPersonCounter_Cd4_2.size() << endl);
	D(cout << "pPersonCounter_Cd4_1.size() = " << pPersonCounter_Cd4_1.size() << endl);}

void Transmission::PushToVector(person * const thePerson)
{
	if(thePerson->Alive()) {
		if(thePerson->GetArtInitiationState())
			pPersonCounter_Art.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 4)
			pPersonCounter_Cd4_4.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 3)
			pPersonCounter_Cd4_3.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 2)
			pPersonCounter_Cd4_2.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 1)
			pPersonCounter_Cd4_1.push_back(thePerson);
	}
}

void Transmission::RemoveFromVector(person * const thePerson)
{
	if(find(pPersonCounter_Art.begin(),pPersonCounter_Art.end(),thePerson) != pPersonCounter_Art.end())
		pPersonCounter_Art.erase(remove(pPersonCounter_Art.begin(),pPersonCounter_Art.end(),thePerson),pPersonCounter_Art.end());
	else if(find(pPersonCounter_Cd4_4.begin(),pPersonCounter_Cd4_4.end(),thePerson) != pPersonCounter_Cd4_4.end())
		pPersonCounter_Cd4_4.erase(remove(pPersonCounter_Cd4_4.begin(),pPersonCounter_Cd4_4.end(),thePerson),pPersonCounter_Cd4_4.end());
	else if(find(pPersonCounter_Cd4_3.begin(),pPersonCounter_Cd4_3.end(),thePerson) != pPersonCounter_Cd4_3.end())
		pPersonCounter_Cd4_3.erase(remove(pPersonCounter_Cd4_3.begin(),pPersonCounter_Cd4_3.end(),thePerson),pPersonCounter_Cd4_3.end());
	else if(find(pPersonCounter_Cd4_2.begin(),pPersonCounter_Cd4_2.end(),thePerson) != pPersonCounter_Cd4_2.end())
		pPersonCounter_Cd4_2.erase(remove(pPersonCounter_Cd4_2.begin(),pPersonCounter_Cd4_2.end(),thePerson),pPersonCounter_Cd4_2.end());
	else if(find(pPersonCounter_Cd4_1.begin(),pPersonCounter_Cd4_1.end(),thePerson) != pPersonCounter_Cd4_1.end())
		pPersonCounter_Cd4_1.erase(remove(pPersonCounter_Cd4_1.begin(),pPersonCounter_Cd4_1.end(),thePerson),pPersonCounter_Cd4_1.end());
}

void Transmission::CalculateBeta()
{
	D(cout << "Beta calculation..." << endl);
	if(theInc->GetIncidenceVectorSize()) {
		SetBeta(theInc->GetIncidenceVectorSize() / GetWeightedTotal());
		D(cout << "beta = " << beta << endl);
		GetIncidenceWeight();
	}
}


double Transmission::GetIncidenceWeight() const
{
	if(theInc->GetIncidenceVectorSize())
		return GetBeta() * GetWeightedTotal() / theInc->GetIncidenceVectorSize();
	else
		return 1;
}

/////////////////////
/////////////////////

size_t Transmission::GetVectorSize_Art() const
{
	return pPersonCounter_Art.size();
}

size_t Transmission::GetVectorSize_Cd4_4() const
{
	return pPersonCounter_Cd4_4.size();
}

size_t Transmission::GetVectorSize_Cd4_3() const
{
	return pPersonCounter_Cd4_3.size();
}

size_t Transmission::GetVectorSize_Cd4_2() const
{
	return pPersonCounter_Cd4_2.size();
}

size_t Transmission::GetVectorSize_Cd4_1() const
{
	return pPersonCounter_Cd4_1.size();
}

double Transmission::GetWeightedTotal() const
{
	/* Infectiousness weights */
	double wArt = 0.1;
	double w500 = 1.35;
	double w350500 = 1;
	double w200350 = 1.64;
	double w200 = 5.17;
	
	/* Calculate individual weights */
	double tArt = wArt * pPersonCounter_Art.size();
	double t500 = w500 * pPersonCounter_Cd4_4.size();
	double t350500 = w350500 * pPersonCounter_Cd4_3.size();
	double t200350 = w200350 * pPersonCounter_Cd4_2.size();
	double t200 = w200 * pPersonCounter_Cd4_1.size();
	
	return(tArt + t500 + t350500 + t200350 + t200);
}

/////////////////////
/////////////////////
