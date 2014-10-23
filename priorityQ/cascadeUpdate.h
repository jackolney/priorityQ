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

//void SeedInitialTestingEvents(person * const thePerson);

void UpdateTreatmentGuidelines(person * const thePerson, unsigned int theCd4, unsigned int theWho);

void ScheduleHctHivTest(person * const thePerson);

void ScheduleVctHivTest(person * const thePerson);

void SchedulePictHivTest(person * const thePerson);

void ScheduleCd4Test(person * const thePerson);

void ScheduleArtInitiation(person * const thePerson);

#endif /* defined(__priorityQ__updateCascade__) */
