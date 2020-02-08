#ifndef RESOURCE_PROSPECTING_DECISIONS_UPDATER_H
#define RESOURCE_PROSPECTING_DECISIONS_UPDATER_H



#include "DecisionsFile.h"
#include "../States/DefaultState.h"



namespace HoI4
{

void updateResourceProspectingDecisions(
	DecisionsFile& resourceProspectingDecisions,
	const std::map<int, int>& _provinceToStateIdMap,
	const std::map<int, HoI4::DefaultState>& defaultStates
);

}





#endif // RESOURCE_PROSPECTING_DECISIONS_UPDATER_H