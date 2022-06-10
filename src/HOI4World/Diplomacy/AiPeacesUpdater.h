#ifndef AI_PEACES_UPDATER_H
#define AI_PEACES_UPDATER_H



#include "src/HOI4World/Diplomacy/AIPeaces.h"
#include <set>



namespace HoI4
{

void updateAiPeaces(AiPeaces& aiPeaces, const std::set<std::string>& majorIdeologies);

}



#endif // AI_PEACES_UPDATER_H