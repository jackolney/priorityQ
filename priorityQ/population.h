//
//  population.h
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__population__
#define __priorityQ__population__

#include <stdio.h>
#include <vector>
#include "person.h"

using namespace std;

class population {
public:
	population(const double theSize); //constructor
	~population(); //destructor
	
	/* Methods */
	void Generate(const double theSize);
	void AddPerson(person * me);
	void AddToVector(person * me);
	
	/* Vector methods */
	void UpdateVector();
	
		//Can I do this simply with pointers to vectors?
		//GetVectorSize(* theVector); ??
		//UpdateVector(* theVector); ??
	
	size_t GetSusceptibleSize_M_0to4() const { return Susceptible_M_0to4.size(); }
	size_t GetSusceptibleSize_M_5to9() const { return Susceptible_M_5to9.size(); }
	size_t GetSusceptibleSize_M_10to14() const { return Susceptible_M_10to14.size(); }
	size_t GetSusceptibleSize_M_15to19() const { return Susceptible_M_15to19.size(); }
	size_t GetSusceptibleSize_M_20to24() const { return Susceptible_M_20to24.size(); }
	size_t GetSusceptibleSize_M_25to29() const { return Susceptible_M_25to29.size(); }
	size_t GetSusceptibleSize_M_30to34() const { return Susceptible_M_30to34.size(); }
	size_t GetSusceptibleSize_M_35to39() const { return Susceptible_M_35to39.size(); }
	size_t GetSusceptibleSize_M_40to44() const { return Susceptible_M_40to44.size(); }
	size_t GetSusceptibleSize_M_45to49() const { return Susceptible_M_45to49.size(); }
	size_t GetSusceptibleSize_M_50to54() const { return Susceptible_M_50to54.size(); }
	size_t GetSusceptibleSize_M_55to59() const { return Susceptible_M_55to59.size(); }
	size_t GetSusceptibleSize_M_60to64() const { return Susceptible_M_60to64.size(); }
	size_t GetSusceptibleSize_M_65to69() const { return Susceptible_M_65to69.size(); }
	size_t GetSusceptibleSize_M_70to74() const { return Susceptible_M_70to74.size(); }
	size_t GetSusceptibleSize_M_75to79() const { return Susceptible_M_75to79.size(); }
	size_t GetSusceptibleSize_M_80() const { return Susceptible_M_80.size(); }
	
	size_t GetSusceptibleSize_F_0to4() const { return Susceptible_F_0to4.size(); }
	size_t GetSusceptibleSize_F_5to9() const { return Susceptible_F_5to9.size(); }
	size_t GetSusceptibleSize_F_10to14() const { return Susceptible_F_10to14.size(); }
	size_t GetSusceptibleSize_F_15to19() const { return Susceptible_F_15to19.size(); }
	size_t GetSusceptibleSize_F_20to24() const { return Susceptible_F_20to24.size(); }
	size_t GetSusceptibleSize_F_25to29() const { return Susceptible_F_25to29.size(); }
	size_t GetSusceptibleSize_F_30to34() const { return Susceptible_F_30to34.size(); }
	size_t GetSusceptibleSize_F_35to39() const { return Susceptible_F_35to39.size(); }
	size_t GetSusceptibleSize_F_40to44() const { return Susceptible_F_40to44.size(); }
	size_t GetSusceptibleSize_F_45to49() const { return Susceptible_F_45to49.size(); }
	size_t GetSusceptibleSize_F_50to54() const { return Susceptible_F_50to54.size(); }
	size_t GetSusceptibleSize_F_55to59() const { return Susceptible_F_55to59.size(); }
	size_t GetSusceptibleSize_F_60to64() const { return Susceptible_F_60to64.size(); }
	size_t GetSusceptibleSize_F_65to69() const { return Susceptible_F_65to69.size(); }
	size_t GetSusceptibleSize_F_70to74() const { return Susceptible_F_70to74.size(); }
	size_t GetSusceptibleSize_F_75to79() const { return Susceptible_F_75to79.size(); }
	size_t GetSusceptibleSize_F_80() const { return Susceptible_F_80.size(); }
	
	size_t GetInfectedSize_M_0to4() const { return Infected_M_0to4.size(); }
	size_t GetInfectedSize_M_5to9() const { return Infected_M_5to9.size(); }
	size_t GetInfectedSize_M_10to14() const { return Infected_M_10to14.size(); }
	size_t GetInfectedSize_M_15to19() const { return Infected_M_15to19.size(); }
	size_t GetInfectedSize_M_20to24() const { return Infected_M_20to24.size(); }
	size_t GetInfectedSize_M_25to29() const { return Infected_M_25to29.size(); }
	size_t GetInfectedSize_M_30to34() const { return Infected_M_30to34.size(); }
	size_t GetInfectedSize_M_35to39() const { return Infected_M_35to39.size(); }
	size_t GetInfectedSize_M_40to44() const { return Infected_M_40to44.size(); }
	size_t GetInfectedSize_M_45to49() const { return Infected_M_45to49.size(); }
	size_t GetInfectedSize_M_50to54() const { return Infected_M_50to54.size(); }
	size_t GetInfectedSize_M_55to59() const { return Infected_M_55to59.size(); }
	size_t GetInfectedSize_M_60to64() const { return Infected_M_60to64.size(); }
	size_t GetInfectedSize_M_65to69() const { return Infected_M_65to69.size(); }
	size_t GetInfectedSize_M_70to74() const { return Infected_M_70to74.size(); }
	size_t GetInfectedSize_M_75to79() const { return Infected_M_75to79.size(); }
	size_t GetInfectedSize_M_80() const { return Infected_M_80.size(); }
	
	size_t GetInfectedSize_F_0to4() const { return Infected_F_0to4.size(); }
	size_t GetInfectedSize_F_5to9() const { return Infected_F_5to9.size(); }
	size_t GetInfectedSize_F_10to14() const { return Infected_F_10to14.size(); }
	size_t GetInfectedSize_F_15to19() const { return Infected_F_15to19.size(); }
	size_t GetInfectedSize_F_20to24() const { return Infected_F_20to24.size(); }
	size_t GetInfectedSize_F_25to29() const { return Infected_F_25to29.size(); }
	size_t GetInfectedSize_F_30to34() const { return Infected_F_30to34.size(); }
	size_t GetInfectedSize_F_35to39() const { return Infected_F_35to39.size(); }
	size_t GetInfectedSize_F_40to44() const { return Infected_F_40to44.size(); }
	size_t GetInfectedSize_F_45to49() const { return Infected_F_45to49.size(); }
	size_t GetInfectedSize_F_50to54() const { return Infected_F_50to54.size(); }
	size_t GetInfectedSize_F_55to59() const { return Infected_F_55to59.size(); }
	size_t GetInfectedSize_F_60to64() const { return Infected_F_60to64.size(); }
	size_t GetInfectedSize_F_65to69() const { return Infected_F_65to69.size(); }
	size_t GetInfectedSize_F_70to74() const { return Infected_F_70to74.size(); }
	size_t GetInfectedSize_F_75to79() const { return Infected_F_75to79.size(); }
	size_t GetInfectedSize_F_80() const { return Infected_F_80.size(); }
	
	
private:
	const double sizeAdjustment;
	unsigned int populationSize;
	
	/* Vector */
	vector<person*> Susceptible_M_0to4;
	vector<person*> Susceptible_M_5to9;
	vector<person*> Susceptible_M_10to14;
	vector<person*> Susceptible_M_15to19;
	vector<person*> Susceptible_M_20to24;
	vector<person*> Susceptible_M_25to29;
	vector<person*> Susceptible_M_30to34;
	vector<person*> Susceptible_M_35to39;
	vector<person*> Susceptible_M_40to44;
	vector<person*> Susceptible_M_45to49;
	vector<person*> Susceptible_M_50to54;
	vector<person*> Susceptible_M_55to59;
	vector<person*> Susceptible_M_60to64;
	vector<person*> Susceptible_M_65to69;
	vector<person*> Susceptible_M_70to74;
	vector<person*> Susceptible_M_75to79;
	vector<person*> Susceptible_M_80;
	
	vector<person*> Susceptible_F_0to4;
	vector<person*> Susceptible_F_5to9;
	vector<person*> Susceptible_F_10to14;
	vector<person*> Susceptible_F_15to19;
	vector<person*> Susceptible_F_20to24;
	vector<person*> Susceptible_F_25to29;
	vector<person*> Susceptible_F_30to34;
	vector<person*> Susceptible_F_35to39;
	vector<person*> Susceptible_F_40to44;
	vector<person*> Susceptible_F_45to49;
	vector<person*> Susceptible_F_50to54;
	vector<person*> Susceptible_F_55to59;
	vector<person*> Susceptible_F_60to64;
	vector<person*> Susceptible_F_65to69;
	vector<person*> Susceptible_F_70to74;
	vector<person*> Susceptible_F_75to79;
	vector<person*> Susceptible_F_80;
	
	vector<person*> Infected_M_0to4;
	vector<person*> Infected_M_5to9;
	vector<person*> Infected_M_10to14;
	vector<person*> Infected_M_15to19;
	vector<person*> Infected_M_20to24;
	vector<person*> Infected_M_25to29;
	vector<person*> Infected_M_30to34;
	vector<person*> Infected_M_35to39;
	vector<person*> Infected_M_40to44;
	vector<person*> Infected_M_45to49;
	vector<person*> Infected_M_50to54;
	vector<person*> Infected_M_55to59;
	vector<person*> Infected_M_60to64;
	vector<person*> Infected_M_65to69;
	vector<person*> Infected_M_70to74;
	vector<person*> Infected_M_75to79;
	vector<person*> Infected_M_80;
	
	vector<person*> Infected_F_0to4;
	vector<person*> Infected_F_5to9;
	vector<person*> Infected_F_10to14;
	vector<person*> Infected_F_15to19;
	vector<person*> Infected_F_20to24;
	vector<person*> Infected_F_25to29;
	vector<person*> Infected_F_30to34;
	vector<person*> Infected_F_35to39;
	vector<person*> Infected_F_40to44;
	vector<person*> Infected_F_45to49;
	vector<person*> Infected_F_50to54;
	vector<person*> Infected_F_55to59;
	vector<person*> Infected_F_60to64;
	vector<person*> Infected_F_65to69;
	vector<person*> Infected_F_70to74;
	vector<person*> Infected_F_75to79;
	vector<person*> Infected_F_80;
	
};

#endif /* defined(__priorityQ__population__) */
