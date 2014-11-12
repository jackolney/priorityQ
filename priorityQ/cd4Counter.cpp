//
//  cd4Counter.cpp
//  priorityQ
//
//  Created by Jack Olney on 10/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "cd4Counter.h"

using namespace std;

/////////////////////
/////////////////////

Cd4Counter::Cd4Counter()
{}

Cd4Counter::~Cd4Counter()
{}

void Cd4Counter::UpdateVector(person * const thePerson)
{
	RemoveFromVector(thePerson);
	PushToVector(thePerson);
}

void Cd4Counter::PushToVector(person * const thePerson)
{
	if(thePerson->Alive() && thePerson->GetSeroStatus()) {
		if(thePerson->GetCurrentCd4() == 4)
			pCd4Counter_4.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 3)
			pCd4Counter_3.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 2)
			pCd4Counter_2.push_back(thePerson);
		else if(thePerson->GetCurrentCd4() == 1)
			pCd4Counter_1.push_back(thePerson);
	}
}

void Cd4Counter::RemoveFromVector(person * const thePerson)
{
	if(find(pCd4Counter_4.begin(),pCd4Counter_4.end(),thePerson) != pCd4Counter_4.end())
		pCd4Counter_4.erase(remove(pCd4Counter_4.begin(),pCd4Counter_4.end(),thePerson),pCd4Counter_4.end());
	else if(find(pCd4Counter_3.begin(),pCd4Counter_3.end(),thePerson) != pCd4Counter_3.end())
		pCd4Counter_3.erase(remove(pCd4Counter_3.begin(),pCd4Counter_3.end(),thePerson),pCd4Counter_3.end());
	else if(find(pCd4Counter_2.begin(),pCd4Counter_2.end(),thePerson) != pCd4Counter_2.end())
		pCd4Counter_2.erase(remove(pCd4Counter_2.begin(),pCd4Counter_2.end(),thePerson),pCd4Counter_2.end());
	else if(find(pCd4Counter_1.begin(),pCd4Counter_1.end(),thePerson) != pCd4Counter_1.end())
		pCd4Counter_1.erase(remove(pCd4Counter_1.begin(),pCd4Counter_1.end(),thePerson),pCd4Counter_1.end());
}

/////////////////////
/////////////////////

size_t Cd4Counter::GetCd4VectorSize_4() const
{
	return pCd4Counter_4.size();
}

size_t Cd4Counter::GetCd4VectorSize_3() const
{
	return pCd4Counter_3.size();
}

size_t Cd4Counter::GetCd4VectorSize_2() const
{
	return pCd4Counter_2.size();
}

size_t Cd4Counter::GetCd4VectorSize_1() const
{
	return pCd4Counter_1.size();
}

/////////////////////
/////////////////////
