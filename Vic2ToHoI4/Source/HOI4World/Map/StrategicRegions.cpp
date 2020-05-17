#include "StrategicRegions.h"
#include "../States/HoI4State.h"
#include "OSCompatibilityLayer.h"
#include <set>



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
