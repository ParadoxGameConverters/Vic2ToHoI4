#include "Navies.h"
#include "external/common_items/Log.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Maps/ProvinceDefinitions.h"



HoI4::Navies::Navies(const std::vector<Vic2::Army>& srcArmies,
	 int backupNavalLocation,
	 const UnitMappings& unitMap,
	 const MtgUnitMappings& mtgUnitMap,
	 const ShipVariants& theShipVariants,
	 const std::map<int, int>& provinceToStateIDMap,
	 std::map<int, State> states,
	 const std::string& tag,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	std::map<std::string, int> usedShipNames;
	for (auto army: srcArmies)
	{
		auto [navalLocation, base] = getLocationAndBase(army.getLocation(),
			 backupNavalLocation,
			 provinceMapper,
			 provinceDefinitions,
			 provinceToStateIDMap,
			 states);

		LegacyNavy newLegacyNavy(army.getName(), navalLocation, base);
		MtgNavy newMtgNavy(army.getName(), navalLocation, base);

		for (const auto& regiment: army.getUnits())
		{
			auto type = regiment.getType();
			auto name = regiment.getName();
			const auto& [unused, inserted] = usedShipNames.insert(std::make_pair(name, 1));
			if (!inserted)
			{
				usedShipNames[name]++;
				name += " " + std::to_string(usedShipNames.at(name));
			}
			if (unitMap.hasMatchingType(type))
			{
				for (const auto& unitInfo: unitMap.getMatchingUnitInfo(type))
				{
					if (unitInfo.getCategory() == "naval" && theShipVariants.hasLegacyVariant(unitInfo.getVersion()))
					{
						LegacyShip newLegacyShip(name, unitInfo.getType(), unitInfo.getEquipment(), tag);
						newLegacyNavy.addShip(newLegacyShip);
					}
				}
			}
			else
			{
				Log(LogLevel::Warning) << "Unknown legacy unit type: " << type;
			}
			if (mtgUnitMap.hasMatchingType(type))
			{
				for (const auto& unitInfo: mtgUnitMap.getMatchingUnitInfo(type))
				{
					if ((unitInfo.getCategory() == "naval") && theShipVariants.hasMtgVariant(unitInfo.getVersion()))
					{
						auto experience = static_cast<float>(regiment.getExperience() / 100);
						MtgShip newMtgShip(name,
							 unitInfo.getType(),
							 unitInfo.getEquipment(),
							 tag,
							 unitInfo.getVersion(),
							 experience);
						newMtgNavy.addShip(newMtgShip);
					}
				}
			}
			else
			{
				Log(LogLevel::Warning) << "Unknown mtg unit type: " << type;
			}
		}

		if (newLegacyNavy.getNumShips() > 0)
		{
			legacyNavies.push_back(newLegacyNavy);
		}
		if (newMtgNavy.getNumShips() > 0)
		{
			mtgNavies.push_back(newMtgNavy);
		}
	}
}


std::tuple<int, int> HoI4::Navies::getLocationAndBase(std::optional<int> vic2Location,
	 int backupNavalLocation,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 const std::map<int, int>& provinceToStateIDMap,
	 std::map<int, State> states)
{
	if (vic2Location == std::nullopt)
	{
		return {backupNavalLocation, backupNavalLocation};
	}

	for (auto possibleProvince: provinceMapper.getVic2ToHoI4ProvinceMapping(*vic2Location))
	{
		if (provinceDefinitions.isSeaProvince(possibleProvince))
		{
			return {possibleProvince, backupNavalLocation};
		}
		if (auto stateID = provinceToStateIDMap.find(possibleProvince); stateID != provinceToStateIDMap.end())
		{
			if (auto state = states.find(stateID->second); state != states.end())
			{
				if (auto mainNavalLocation = state->second.getMainNavalLocation(); mainNavalLocation)
				{
					return {*mainNavalLocation, *mainNavalLocation};
				}
			}
		}
	}

	return {backupNavalLocation, backupNavalLocation};
}