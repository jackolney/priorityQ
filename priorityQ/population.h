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

class population {
public:
	population(const double theSize); //constructor
	~population(); //destructor

	/* Methods */
	void Generate(const double theSize);
	
private:
	const double populationSize;
	
};

#endif /* defined(__priorityQ__population__) */
