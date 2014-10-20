//
//  update.h
//  priorityQ
//
//  Created by Jack Olney on 16/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__update__
#define __priorityQ__update__

#include <stdio.h>
#include "person.h"

void SeedEvents(person * const thePerson, const double Time);

void UpdateEvents(person * const thePerson);

void UpdateAge(person * const thePerson);

void ScheduleCd4Test(person * const thePerson);

void ScheduleArtInitiation(person * const thePerson);

#endif /* defined(__priorityQ__update__) */
