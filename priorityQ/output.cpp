//
//  output.cpp
//  priorityQ
//
//  Created by Jack Olney on 28/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "output.h"

using namespace std;

double careExperienceAmongHivRelatedDeaths [5]; //NeverDiagnosed, DiagnosedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.


void FillOutCareExperienceArray(person * const thePerson, const double theTime)
{
	if(thePerson->GetHivDeath() && theTime >= 14610 && theTime < 21915) {
			//NeverDiagnosed
		careExperienceAmongHivRelatedDeaths[0] += !thePerson->GetDiagnosedState();
			//DiagnosedButNeverInitiatedArt
		careExperienceAmongHivRelatedDeaths[1] += (thePerson->GetDiagnosedState() && !thePerson->GetEverArt());
			//ArtLate
		careExperienceAmongHivRelatedDeaths[2] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() == 1);
			//ArtButDiedOffArt
		careExperienceAmongHivRelatedDeaths[3] += (thePerson->GetEverArt() && !thePerson->GetArtDeath());
			//ArtEarly
		careExperienceAmongHivRelatedDeaths[4] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() > 1);
	}
	for(size_t i=0 ; i<5; i++)
		cout << careExperienceAmongHivRelatedDeaths[i] << endl;
}
