//
//  transmissionEvents.h
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__transmissionEvents__
#define __priorityQ__transmissionEvents__

#include <stdio.h>
#include "event.h"
#include "transmission.h"

class GetBeta : public event {
public:
	GetBeta(Transmission * const theTrans, const double Time); //constructor
	~GetBeta(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	Transmission * const pTransmission;
};

#endif /* defined(__priorityQ__transmissionEvents__) */
