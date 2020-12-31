#include "SupplyZones.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "HOI4World/States/DefaultState.h"
#include "HOI4World/States/HoI4State.h"
#include "HOI4World/States/HoI4States.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "SupplyArea.h"
#include "SupplyZone.h"



HoI4::SupplyZones::SupplyZones(const std::map<int, DefaultState>& defaultStates, const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tImporting supply zones";
	importStates(defaultStates);

	registerKeyword("supply_area", [this](const std::string& unused, std::istream& theStream) {
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