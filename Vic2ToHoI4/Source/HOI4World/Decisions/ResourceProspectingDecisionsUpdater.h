#ifndef RESOURCE_PROSPECTING_DECISIONS_UPDATER_H
#define RESOURCE_PROSPECTING_DECISIONS_UPDATER_H



#include "DecisionsFile.h"



namespace HoI4
{

void updateResourceProspectingDecisions(
	DecisionsFile& resourceProspectingDecisions,
	const std::map<int, int>& _provinceToStateIdMap
);

}





#endif // RESOURCE_PROSPECTING_DECISIONS_UPDATER_H