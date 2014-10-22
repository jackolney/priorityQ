//
//  person.h
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__person__
#define __priorityQ__person__

#include <stdio.h>

class person {
public:
	person(const double Time); //constuctor
	virtual ~person(); //destructor
	
	/* Initialiser functions */
	bool AssignGender();
	void AssignInitialAge(const double Time);
	double GenerateNatDeathDate();
	double AssignNatDeathDate(const double Time);
	
	/* Methods */
	void Kill(const double Time);
	double SetAge(const double Time);

	/* Hiv Acquisition Functions */
	bool CheckHiv(const double Time);
	void SetSeroStatus(const bool theState) { seroStatus = theState; }
	void SetSeroconversionDay(const double Time) { seroconversionDay = Time; }
	void SetHivIndicators();
	void SetInitialCd4Count();
	void SetInitialWhoStage();
	
	/* Hiv Progression Functions */
	void ScheduleHivIndicatorUpdate();
	void SetCurrentCd4Count(unsigned int theCount) { currentCd4 = theCount; }
	void SetCurrentWhoStage(unsigned int theStage) { currentWho = theStage; }
	double GenerateHivDeathDate(); //function returns the HivDeathDate Value;
	void AssignHivDeathDate(); //function creates the Death event.
	
	/* Hiv Care Functions */
	void SetDiagnosedState(const bool theState) { diagnosed = theState; }
	void SetCd4TestState(const bool theState) { cd4Test = theState; }
	void SetArtInitiationState(const bool theState) { art = theState; }
	
	/* Accessor methods */
	bool GetGender() const;
	double GetNatDeathDate() const;
	bool Alive() const;
	double GetAge() const;
	const double GetBirthDay() const { return BirthDay; }
	unsigned int GetCurrentCd4() const { return currentCd4; }
	unsigned int GetCurrentWho() const { return currentWho; }
	bool GetDiagnosedState() const { return diagnosed; }
	bool GetCd4TestState() const { return cd4Test; }
	bool GetArtInitiationState() const { return art; }
	bool GetSeroStatus() const { return seroStatus; }
	double GetHivDeathDate() const { return HivDeathDate; }
	double GetCd4DeclineDate() const { return Cd4DeclineDate; }
	double GetCd4RecoverDate() const { return Cd4RecoverDate; }
	double GetWhoDeclineDate() const { return WhoDeclineDate; }
	double GetWhoRecoverDate() const { return WhoRecoverDate; }
	
private:
	/* basic characteristics */
	bool gender;
	double currentAge;
	double initialAge;
	double natDeathDate;
	
	/* HIV status */
	bool seroStatus;
	double seroconversionDay;
	double hivDeathDate;
	
	unsigned int currentCd4;
	unsigned int initialCd4;
	unsigned int currentWho;
	unsigned int initialWho;
	
	/* Day = time an event occured */
	double DeathDay;
	const double BirthDay;
	
	/* Date = time an event will occur */
	double HivDeathDate;
	double Cd4DeclineDate;
	double Cd4RecoverDate;
	double WhoDeclineDate;
	double WhoRecoverDate;
	
	
	/* HIV care */
	bool diagnosed;
	bool inCare;
	bool cd4Test;
	bool cd4Result;
	bool art;
};

#endif /* defined(__priorityQ__person__) */