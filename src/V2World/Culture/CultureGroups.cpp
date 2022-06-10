#include "src/V2World/Culture/CultureGroups.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"



std::optional<std::string> Vic2::CultureGroups::getGroup(const std::string& culture) const
{
	if (!mappings.contains(culture))
	{
		return std::nullopt;
	}

	return mappings.at(culture);
}