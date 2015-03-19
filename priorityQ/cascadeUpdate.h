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
void ScheduleVctHivTest(person * const thePerson, const double theTime);

void SchedulePictHivTest(person * const thePerson, const double theTime);

/* Linkage */
bool VctLinkage(person * const thePerson);

bool PictLinkage(person * const thePerson);

/* Initial Cd4 test */
void ScheduleInitialCd4TestAfterHct(person * const thePerson, const double theTime);

/* Pre-Art Cd4 Test */
void SchedulePreArtCd4Test(person * const thePerson, const double theTime);

/* Cd4 Test Result */
void ScheduleCd4TestResult(person * const thePerson, const double theTime);

bool ReceiveCd4TestResult(person * const thePerson, const double theTime);

bool AttendCd4TestResult(person * const thePerson, const double theTime);

bool SecondaryCd4Test(person * const thePerson, const double theTime);

void FastTrackArt(person * const thePerson, const double theTime);

/* Art Care */
void ScheduleArtInitiation(person * const thePerson, const double theTime);

void ScheduleArtDropout(person * const thePerson, const double theTime);

#endif /* defined(__priorityQ__updateCascade__) */
