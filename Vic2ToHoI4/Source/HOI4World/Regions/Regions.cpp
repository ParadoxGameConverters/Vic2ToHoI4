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


std::vector<std::string> HoI4::Regions::getSubregions(const std::string& regionName) const
{
	if (const auto& subregions = regionSubregions.find(regionName); subregions != regionSubregions.end())
	{
		return subregions->second;
	}

	return std::vector<std::string>{};
}


std::vector<std::string> HoI4::Regions::getBlockedRegions(const std::string& regionName) const
{
	if (const auto& blocked = regionBlocked.find(regionName); blocked != regionBlocked.end())
	{
		return blocked->second;
	}

	return std::vector<std::string>{};
}


std::vector<std::string> HoI4::Regions::getSuperregions(const std::string& regionName) const
{
	std::vector<std::string> superregions;
	for (const auto& [region, subregions]: regionSubregions)
	{
		if (std::find(subregions.begin(), subregions.end(), regionName) != subregions.end())
		{
			superregions.push_back(region);
		}
	}

	return superregions;
}


bool HoI4::Regions::isRegionBlocked(const std::string& stateRegion, const std::string& ownerRegion) const
{
	if (stateRegion == ownerRegion)
	{
		return true;
	}

	const auto& blockedRegions = getBlockedRegions(ownerRegion);
	if (std::find(blockedRegions.begin(), blockedRegions.end(), stateRegion) != blockedRegions.end())
	{
		return true;
	}
	for (const auto& superregion: getSuperregions(stateRegion))
	{
		if (std::find(blockedRegions.begin(), blockedRegions.end(), superregion) != blockedRegions.end())
		{
			return true;
		}
	}
	return false;
}