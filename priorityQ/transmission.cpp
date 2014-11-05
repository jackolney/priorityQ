//
//  transmission.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "transmission.h"

using namespace std;

/////////////////////
/////////////////////

Transmission::Transmission() :
referenceYear(11687.04),
beta(0)
{}

Transmission::~Transmission()
{}

void Transmission::UpdateVector(person * const thePerson)
{
	RemoveFromVector(thePerson);
	PushToVector(thePerson);
	
	cout << "pPersonCounter_Art.size() = " << pPersonCounter_Art.size() << endl;
	cout << "pPersonCounter_Cd4_4.size() = " << pPersonCounter_Cd4_4.size() << endl;
	cout << "pPersonCounter_Cd4_3.size() = " << pPersonCounter_Cd4_3.size() << endl;
	cout << "pPersonCounter_Cd4_2.size() = " << pPersonCounter_Cd4_2.size() << endl;
	cout << "pPersonCounter_Cd4_1.size() = " << pPersonCounter_Cd4_1.size() << endl;
}

void Transmission::PushToVector(person * const thePerson)
{
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

/////////////////////
/////////////////////