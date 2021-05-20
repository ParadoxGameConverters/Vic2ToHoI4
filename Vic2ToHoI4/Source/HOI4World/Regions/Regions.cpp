#include "Regions.h"



std::optional<std::string> HoI4::Regions::getRegion(int provinceNumber) const
{
	if (const auto& region = regionsMap.find(provinceNumber); region != regionsMap.end())
	{
		return region->second;
	}

	return std::nullopt;
}


std::optional<std::string> HoI4::Regions::getRegionName(const std::string& regionName) const
{
	if (const auto& name = regionNames.find(regionName); name != regionNames.end())
	{
		return name->second;
	}

	return std::nullopt;
}


std::optional<std::string> HoI4::Regions::getRegionAdjective(const std::string& regionName) const
{
	if (const auto& adjective = regionAdjectives.find(regionName); adjective != regionAdjectives.end())
	{
		return adjective->second;
	}

	return std::nullopt;
}