#include "CultureGroups.h"
#include "Configuration.h"
#include "OSCompatibilityLayer.h"



std::optional<std::string> Vic2::CultureGroups::getGroup(const std::string& culture) const
{
	if (!mappings.count(culture))
	{
		return std::nullopt;
	}

	return mappings.at(culture);
}