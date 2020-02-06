#ifndef OUT_AI_PEACES
#define OUT_AI_PEACES



#include "../../HOI4World/Diplomacy/AIPeaces.h"
#include "../../Configuration.h"
#include <set>



namespace HoI4
{

void outAiPeaces(
	const AiPeaces& aiPeaces,
	const std::set<std::string>& majorIdeologies,
	const Configuration& theConfiguration
);

}



#endif // OUT_AI_PEACES