#include "StrategicRegions.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <set>



void HoI4::StrategicRegions::convert(const States& theStates)
{
	Log(LogLevel::Info) << "\tConverting strategic regions";

	for (const auto& state: theStates.getStates())
	{
		const auto usedRegions = determineUsedRegions(state.second);
		const auto bestRegion = determineMostUsedRegion(usedRegions);
		if (bestRegion)
		{
			addProvincesToRegion(*bestRegion, state.second);
		}
	}

	addLeftoverProvincesToRegions();
}


std::map<int, int> HoI4::StrategicRegions::determineUsedRegions(const State& state)
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

		usedRegions[mapping->second]++;
		provinceToStrategicRegionMap.erase(mapping);
	}

	return usedRegions;
}


std::optional<int> HoI4::StrategicRegions::determineMostUsedRegion(const std::map<int, int>& usedRegions)
{
	if (!usedRegions.empty())
	{
		return std::max_element(usedRegions.begin(),
			 usedRegions.end(),
			 [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				 return a.second < b.second;
			 })
			 ->first;
	}

	return std::nullopt;
}


void HoI4::StrategicRegions::addLeftoverProvincesToRegions()
{
	for (const auto& mapping: provinceToStrategicRegionMap)
	{
		addProvinceToRegion(mapping.second, mapping.first);
	}
}


void HoI4::StrategicRegions::addProvincesToRegion(int regionNumber, const State& state)
{
	for (const auto& province: state.getProvinces())
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

	for (const auto& filename:
		 commonItems::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/map/strategicregions/"))
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
