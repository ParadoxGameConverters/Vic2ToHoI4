#include "src/HOI4World/OperativeNames/OperativeNamesMappings.h"



std::string HoI4::OperativeNamesMappings::getMatchingNamesSet(const std::string& primaryCulture) const
{
	if (const auto& mapping = cultureToNamesSetMap.find(primaryCulture); mapping != cultureToNamesSetMap.end())
	{
		return mapping->second;
	}
	else
	{
		return "GENERIC_ENG_OPERATIVE_CODENAME_HISTORICAL";
	}
}