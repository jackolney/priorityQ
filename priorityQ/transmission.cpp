//
//  transmissionProbability.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "transmission.h"
#include "update.h"

using namespace std;

/////////////////////
/////////////////////

Transmission::Transmission(population * thePop) :
pPop(thePop),
referenceYear(11688),
beta(0)
{
	for(size_t i=0;i<5;i++)
		PersonCounter[i] = 0;
	ScheduleBetaCalculation();
}

Transmission::~Transmission()
{}

void Transmission::UpdateVector(person * const thePerson)
{
	SwapOut(thePerson);
	PushIn(thePerson);
}

void Transmission::PushIn(person * const thePerson)
{
	if(thePerson->Alive() && thePerson->GetSeroStatus()) {
		size_t index = 0;
		if(thePerson->GetArtInitiationState())
			index = 0;
		else switch(thePerson->GetCurrentCd4()) {
			case 1: index = 1; break;
			case 2: index = 2; break;
			case 3: index = 3; break;
			case 4: index = 4; break;
		}
		PersonCounter[index]++;
		thePerson->SetInfectiousnessIndex(index);
	}
}

void Transmission::SwapOut(person * const thePerson)
{
	if(thePerson->GetInfectiousnessIndex() != -1)
		PersonCounter[thePerson->GetInfectiousnessIndex()]--;
}

void Transmission::CalculateBeta()
{
	D(cout << "Beta calculation..." << endl);
	beta = pPop->GetInfectedCases() / GetWeightedTotal();
	cout << "Inf = " << pPop->GetInfectedCases() << endl;
	cout << "WeightedTotal = " << GetWeightedTotal() << endl;
	cout << "Total array = " << PersonCounter[0] + PersonCounter[1] + PersonCounter[2] + PersonCounter[3] + PersonCounter[4] << endl;
	cout << "Beta is = " << beta << endl;
}

/////////////////////
/////////////////////

double Transmission::GetWeightedTotal() const
{
	/* Infectiousness weights */
	double wArt = 0.1;
	double w500 = 1.35;
	double w350500 = 1;
	double w200350 = 1.64;
	double w200 = 5.17;
	
	/* Calculate individual weights */
	double tArt = wArt * PersonCounter[0];
	double t200 = w200 * PersonCounter[1];
	double t200350 = w200350 * PersonCounter[2];
	double t350500 = w350500 * PersonCounter[3];
	double t500 = w500 * PersonCounter[4];
	
	return(tArt + t500 + t350500 + t200350 + t200);
}

/////////////////////
/////////////////////
