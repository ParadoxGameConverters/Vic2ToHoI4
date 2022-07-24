#include "src/V2World/Culture/CultureGroups.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"



std::optional<std::string> Vic2::CultureGroups::GetGroup(const std::string& culture) const
{
	if (!mappings_.contains(culture))
	{
		return std::nullopt;
	}

	return mappings_.at(culture);
}


bool Vic2::CultureGroups::IsUnionCountry(const std::string& tag) const
{
	return union_tags_.contains(tag);
}