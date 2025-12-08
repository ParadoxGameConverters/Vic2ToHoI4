#ifndef OUT_FACTION_RULES_H
#define OUT_FACTION_RULES_H



#include "src/HOI4World/Factions/FactionRule.h"



namespace HoI4
{

void outputFactionRules(const std::filesystem::path& outputName, const std::vector<FactionRule>& factionRules);

} // namespace HoI4



#endif // OUT_FACTION_RULES_H