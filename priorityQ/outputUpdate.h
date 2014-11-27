//
//  outputUpdate.h
//  priorityQ
//
//  Created by Jack Olney on 30/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__outputUpdate__
#define __priorityQ__outputUpdate__

#include <stdio.h>
#include "person.h"

void WritePop(person * const thePerson);

void WriteHiv(person * const thePerson);

void WriteArt(person * const thePerson);

void WriteCare(person * const thePerson, const double theTime);

void WriteAidsDeath(person * const thePerson);

void Write2007(person * const thePerson);

void Write2012(person * const thePerson);

void Write2014(person * const thePerson);

void WriteCd4(person * const thePerson);

void WriteWho(person * const thePerson);

void WriteIncidence(unsigned int const &theIncidentCases);

#endif /* defined(__priorityQ__outputUpdate__) */
