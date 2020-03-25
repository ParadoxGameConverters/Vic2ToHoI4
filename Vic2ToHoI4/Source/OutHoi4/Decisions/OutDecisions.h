#ifndef OUT_DECISIONS_H
#define OUT_DECISIONS_H



#include "../../Configuration.h"
#include "../../HOI4World/Decisions/Decisions.h"



namespace HoI4
{

void outputDecisions(decisions& theDecisions,
	 const std::set<std::string>& majorIdeologies,
	 const Configuration& theConfiguration);

}



#endif // OUT_DECISIONS_H
