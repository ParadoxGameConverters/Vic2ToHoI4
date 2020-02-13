#ifndef DECISIONS_OUTPUTTER
#define DECISIONS_OUTPUTTER



#include "../../HOI4World/Decisions/Decisions.h"
#include "../../Configuration.h"



namespace HoI4
{
	
void outputDecisions(
	decisions& theDecisions,
	const std::set<std::string>& majorIdeologies,
	const Configuration& theConfiguration
);

}




#endif // DECISIONS_OUTPUTTER
