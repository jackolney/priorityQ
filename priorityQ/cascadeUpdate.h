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

void UpdateTreatmentGuidelines(person * const thePerson, unsigned int theCd4, unsigned int theWho);

/* Hiv Testing */
void ScheduleHctHivTest(person * const thePerson);

void ScheduleVctHivTest(person * const thePerson);

void SchedulePictHivTest(person * const thePerson);

/* Linkage */
double HctLinkage(person * const thePerson);

double VctLinkage(person * const thePerson);

double PictLinkage(person * const thePerson);


/* Pre-Art Care */
void ScheduleCd4Test(person * const thePerson);

/* Art Care */
void ScheduleArtInitiation(person * const thePerson);

#endif /* defined(__priorityQ__updateCascade__) */
