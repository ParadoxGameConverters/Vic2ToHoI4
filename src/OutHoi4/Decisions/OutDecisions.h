#ifndef OUT_DECISIONS_H
#define OUT_DECISIONS_H



#include "HOI4World/Decisions/Decisions.h"



namespace HoI4
{

void outputDecisions(const decisions& theDecisions,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName);

}



#endif // OUT_DECISIONS_H