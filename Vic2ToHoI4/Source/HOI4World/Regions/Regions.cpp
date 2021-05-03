#include "Regions.h"



std::optional<std::string> HoI4::Regions::getRegion(int provinceNumber) const
{
	if (regionsMap.contains(provinceNumber))
	{
		return regionsMap.at(provinceNumber);
	}

	return std::nullopt;
}


std::optional<std::string> HoI4::Regions::getRegionName(const std::string& regionName) const
{
	if (regionNames.contains(regionName))
	{
		return regionNames.at(regionName);
	}

	return std::nullopt;
}


std::optional<std::string> HoI4::Regions::getRegionAdjective(const std::string& regionName) const
{
	if (regionAdjectives.contains(regionName))
	{
		return regionAdjectives.at(regionName);
	}

	return std::nullopt;
}