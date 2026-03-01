#ifndef OUT_FACTION_TEMPLATES_H
#define OUT_FACTION_TEMPLATES_H



#include "src/HOI4World/Factions/FactionTemplate.h"



namespace HoI4
{

void outputFactionTemplates(const std::filesystem::path& outputName,
	 const std::vector<FactionTemplate>& factionTemplates);

} // namespace HoI4



#endif // OUT_FACTION_TEMPLATES_H