#include "src/HOI4World/Map/SupplyZones.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/SupplyArea.h"
#include "src/HOI4World/Map/SupplyZone.h"
#include "src/HOI4World/States/DefaultState.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"



HoI4::SupplyZones::SupplyZones(const std::map<int, DefaultState>& defaultStates, const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tImporting supply zones";
	importStates(defaultStates);

	registerKeyword("supply_area", [this](std::istream& theStream) {
		const SupplyArea area(theStream);
		auto ID = area.getID();

		SupplyZone newSupplyZone(ID, area.getValue());
		supplyZones.insert(std::make_pair(ID, newSupplyZone));

		for (auto state: area.getStates())
		{
			auto mapping = defaultStateToProvinceMap.find(state);
			for (auto province: mapping->second)
			{
				provinceToSupplyZoneMap.insert(std::make_pair(province, ID));
			}
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	for (const auto& supplyZonesFile:
		 commonItems::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/map/supplyareas"))
	{
		auto num = stoi(supplyZonesFile.substr(0, supplyZonesFile.find_first_of('-')));
		supplyZonesFileNames.insert(make_pair(num, supplyZonesFile));
		parseFile(theConfiguration.getHoI4Path() + "/map/supplyareas/" + supplyZonesFile);
	}

	clearRegisteredKeywords();
}


void HoI4::SupplyZones::importStates(const std::map<int, DefaultState>& defaultStates)
{
	for (const auto& state: defaultStates)
	{
		defaultStateToProvinceMap.insert(make_pair(state.first, state.second.getProvinces()));
	}
}


void HoI4::SupplyZones::convertSupplyZones(const States& states)
{
	Log(LogLevel::Info) << "\tConverting supply zones";
	for (const auto& state: states.getStates())
	{
		for (auto province: state.second.getProvinces())
		{
			if (auto mapping = provinceToSupplyZoneMap.find(province); mapping != provinceToSupplyZoneMap.end())
			{
				if (auto supplyZone = supplyZones.find(mapping->second); supplyZone != supplyZones.end())
				{
					supplyZone->second.addState(state.first);
					break;
				}
			}
		}
	}
}


std::optional<std::string> HoI4::SupplyZones::getSupplyZoneFileName(const int supplyZoneNum) const
{
	if (const auto filenameMap = supplyZonesFileNames.find(supplyZoneNum); filenameMap != supplyZonesFileNames.end())
	{
		return filenameMap->second;
	}

	return std::nullopt;
}