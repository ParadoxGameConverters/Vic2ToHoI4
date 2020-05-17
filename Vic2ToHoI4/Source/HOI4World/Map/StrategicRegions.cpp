#include "StrategicRegions.h"
#include "../States/HoI4State.h"
#include "../States/HoI4States.h"
#include "OSCompatibilityLayer.h"
#include <set>



void HoI4::StrategicRegions::convert(const States& theStates)
{
	Log(LogLevel::Info) << "\tConverting strategic regions";

	for (auto state: theStates.getStates())
	{
		std::map<int, int> usedRegions = determineUsedRegions(state.second);
		auto bestRegion = determineMostUsedRegion(usedRegions);
		if (bestRegion)
		{
			addProvincesToRegion(*bestRegion, state.second);
		}
	}
	addLeftoverProvincesToRegions(provinceToStrategicRegionMap);
}


std::map<int, int> HoI4::StrategicRegions::determineUsedRegions(const HoI4::State& state)
{
	std::map<int, int> usedRegions; // region ID -> number of provinces in that region

	for (auto province: state.getProvinces())
	{
		auto mapping = provinceToStrategicRegionMap.find(province);
		if (mapping == provinceToStrategicRegionMap.end())
		{
			Log(LogLevel::Warning) << "Province " << province << " had no original strategic region";
			continue;
		}

		auto usedRegion = usedRegions.find(mapping->second);
		if (usedRegion == usedRegions.end())
		{
			usedRegions.insert(std::make_pair(mapping->second, 1));
		}
		else
		{
			usedRegion->second++;
		}

		provinceToStrategicRegionMap.erase(mapping);
	}

	return usedRegions;
}


std::optional<int> HoI4::StrategicRegions::determineMostUsedRegion(const std::map<int, int>& usedRegions) const
{
	int mostProvinces = 0;
	std::optional<int> bestRegion;
	for (auto region: usedRegions)
	{
		if (region.second > mostProvinces)
		{
			bestRegion = region.first;
			mostProvinces = region.second;
		}
	}

	return bestRegion;
}


void HoI4::StrategicRegions::addLeftoverProvincesToRegions(const std::map<int, int>& provinceToStrategicRegionMap)
{
	for (auto mapping: provinceToStrategicRegionMap)
	{
		addProvinceToRegion(mapping.second, mapping.first);
	}
}


void HoI4::StrategicRegions::addProvincesToRegion(int regionNumber, const HoI4::State& state)
{
	for (auto province: state.getProvinces())
	{
		addProvinceToRegion(regionNumber, province);
	}
}


void HoI4::StrategicRegions::addProvinceToRegion(int regionNumber, int provinceId)
{
	auto region = strategicRegions.find(regionNumber);
	if (region == strategicRegions.end())
	{
		Log(LogLevel::Warning) << "Strategic region " << regionNumber << " was not in the list of regions.";
		return;
	}

	region->second.addNewProvince(provinceId);
}



std::unique_ptr<HoI4::StrategicRegions> HoI4::StrategicRegions::Factory::importStrategicRegions(
	 const Configuration& theConfiguration)
{
	std::map<int, StrategicRegion> strategicRegions;
	std::map<int, int> provinceToStrategicRegionMap;

	std::set<std::string> fileNames;
	Utils::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/map/strategicregions/", fileNames);
	for (const auto& filename: fileNames)
	{
		auto newRegion = StrategicRegion(filename, theConfiguration);
		strategicRegions.insert(std::make_pair(newRegion.getID(), newRegion));

		for (auto province: newRegion.getOldProvinces())
		{
			provinceToStrategicRegionMap.insert(std::make_pair(province, newRegion.getID()));
		}
	}

	return std::make_unique<StrategicRegions>(std::move(strategicRegions), std::move(provinceToStrategicRegionMap));
}
