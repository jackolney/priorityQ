//
//  toolbox.h
//  priorityQ
//
//  Created by Jack Olney on 23/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef priorityQ_toolbox_h
#define priorityQ_toolbox_h

/* Hiv testing times */
const double hctHivTestTime = 1 * 365.25;

const double vctHivTestTime = 5.8 * 365.25;

const double pictHivTestTime_AsymptomaticNoCd4Result = 2 * 365.25;
const double pictHivTestTime_AsymptomaticCd4ResultNotEligible = 1 * 365.25;
const double pictHivTestTime_AsymptomaticCd4ResultEligible = 0.5 * 365.25;
const double pictHivTestTime_SymptomaticOblivious = 1 * 365.25;
const double pictHivTestTime_SymptomaticNoCd4Result = 0.5 * 365.25;
const double pictHivTestTime_SymptomaticCd4Result = 0.5 * 365.25;


/* Linkage probabilities */
const double hctProbLink = 0.054;
const double hctProbLinkPreviouslyDiagnosed = 0.2;
const double vctProbLink = 0.59;
const double pictProbLink = 0.54;

/* HCT time between Hiv test and Cd4 test */
const double hctCd4TestTime_Cd4_4 = 93;
const double hctCd4TestTime_Cd4_3 = 97;
const double hctCd4TestTime_Cd4_2 = 152.5;
const double hctCd4TestTime_Cd4_1 = 142;

/* Time between Cd4 test and receiving results */
const double cd4ResultTime = 30;

/* Time between receiving result Cd4 test and subsequent Cd4 test */
const double cd4TestTime = 335.25;

/* Pre-Art retention probability */
const double hctShortTermRetention = 0.6192;
const double hctLongTermRetention = 0.6192;

const double vctShortTermRetention = 0.5326;
const double vctLongTermRetention = 0.5326;

const double pictShortTermRetention = 0.5407;
const double pictLongTermRetention = 0.5407;

/* Time between eligiblity and Art initiation */
const double artInitiationTime = 217.07;

/* Time between being lost from Art care and returning */
const double artReturnTime = 3 * 365.25;

#endif