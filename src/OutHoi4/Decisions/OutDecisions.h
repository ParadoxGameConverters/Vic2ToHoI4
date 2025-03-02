#ifndef OUT_DECISIONS_H
#define OUT_DECISIONS_H



#include "src/HOI4World/Decisions/Decisions.h"



namespace HoI4
{

void outputDecisions(const decisions& theDecisions,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName);

}



#endif // OUT_DECISIONS_H