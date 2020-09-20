#include "CultureGroups.h"
#include "../../Configuration.h"
#include "OSCompatibilityLayer.h"



std::optional<std::string> Vic2::CultureGroups::getGroup(const std::string& culture) const
{
	if (auto mapping = mappings.find(culture); mapping != mappings.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}