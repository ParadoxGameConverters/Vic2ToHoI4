#ifndef RESOURCE_PROSPECTING_DECISIONS_H
#define RESOURCE_PROSPECTING_DECISIONS_H



#include "DecisionsFile.h"
#include "../States/DefaultState.h"



namespace HoI4
{

class ResourceProspectingDecisions: public DecisionsFile
{
	public:
		void updateDecisions(
			const std::map<int, int>& _provinceToStateIdMap,
			const std::map<int, DefaultState>& defaultStates);
};

}





#endif // RESOURCE_PROSPECTING_DECISIONS_H