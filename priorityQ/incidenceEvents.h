//
//  incidenceEvents.h
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__incidenceEvents__
#define __priorityQ__incidenceEvents__

#include <stdio.h>
#include "event.h"
#include "incidence.h"

class SeedIncidence : public event {
public:
	SeedIncidence(Incidence * theIncidence, const double Time); //constructor
	~SeedIncidence(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	Incidence * pInc;
};

#endif /* defined(__priorityQ__incidenceEvents__) */
