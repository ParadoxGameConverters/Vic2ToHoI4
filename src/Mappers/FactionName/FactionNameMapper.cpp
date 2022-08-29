#include "src/Mappers/FactionName/FactionNameMapper.h"
#include <algorithm>



std::optional<std::string> Mappers::FactionNameMapper::getFactionName(const std::string& HoI4Ideology,
	 const std::string& Hoi4Culture,
	 const std::string& Hoi4CultureGroup)
{
	for (const auto& mapping: mappings)
	{
		if ((mapping.hoi4Ideology == "any" || HoI4Ideology == mapping.hoi4Ideology) &&
			 (mapping.hoi4Culture == "any" || Hoi4Culture == mapping.hoi4Culture ||
				  Hoi4CultureGroup == mapping.hoi4Culture))
		{
			std::string factionName = mapping.factionName;
			auto hasSameName = [factionName](const FactionNameMapping& faction) -> bool {
				return (faction.factionName == factionName);
			};

			mappings.erase(std::remove_if(mappings.begin(), mappings.end() - 1, (hasSameName)));
			return factionName;
		}
	}

	return std::nullopt;
}