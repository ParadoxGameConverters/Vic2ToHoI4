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


std::optional<std::string> HoI4::Regions::getRegionLevel(const std::string& regionName) const
{
	if (const auto& level = regionLevels.find(regionName); level != regionLevels.end())
	{
		return level->second;
	}

	return std::nullopt;
}


std::vector<std::string> HoI4::Regions::getRegionGeography(const std::string& regionName) const
{
	if (const auto& geography = regionGeographies.find(regionName); geography != regionGeographies.end())
	{
		return geography->second;
	}

	return std::vector<std::string>{};
}


std::vector<std::string> HoI4::Regions::getRegionBlocked(const std::string& regionName) const
{
	if (const auto& blocked = regionBlocked.find(regionName); blocked != regionBlocked.end())
	{
		return blocked->second;
	}

	return std::vector<std::string>{};
}