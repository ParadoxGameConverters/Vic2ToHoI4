#ifndef OUT_FACTION_GOALS_H
#define OUT_FACTION_GOALS_H



#include "src/HOI4World/Factions/FactionGoal.h"



namespace HoI4
{

void outputFactionGoals(const std::filesystem::path& outputName,
	 const std::vector<FactionGoal>& factionGoals,
	 const std::map<std::string, double>& variables);

} // namespace HoI4



#endif // OUT_FACTION_GOALS_H