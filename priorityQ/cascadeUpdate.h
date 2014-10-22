//
//  updateCascade.h
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__updateCascade__
#define __priorityQ__updateCascade__

#include <stdio.h>
#include "person.h"

void SeedEvents(person * const thePerson, const double Time);

void ScheduleCd4Test(person * const thePerson);

void ScheduleArtInitiation(person * const thePerson);

#endif /* defined(__priorityQ__updateCascade__) */
