#include "Navies.h"
#include "../../Mappers/ProvinceDefinitions.h"
#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "Log.h"



HoI4::Navies::Navies(const std::vector<Vic2::Army>& srcArmies,
	 int backupNavalLocation,
	 const UnitMappings& unitMap,
	 const MtgUnitMappings& mtgUnitMap,
	 const ShipVariants& theShipVariants,
	 const std::map<int, int>& provinceToStateIDMap,
	 std::map<int, State> states,
	 const std::string& tag)
{
	for (auto army: srcArmies)
	{
		auto navalLocation = backupNavalLocation;
		auto base = backupNavalLocation;

		if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(army.getLocation()); mapping)
		{
			for (auto possibleProvince: *mapping)
			{
				if (provinceDefinitions::isSeaProvince(possibleProvince))
				{
					navalLocation = possibleProvince;
					break;
				}
				else if (auto stateID = provinceToStateIDMap.find(possibleProvince); stateID != provinceToStateIDMap.end())
				{
					if (auto state = states.find(stateID->second); state != states.end())
					{
						if (auto mainNavalLocation = state->second.getMainNavalLocation(); mainNavalLocation)
						{
							navalLocation = *mainNavalLocation;
							base = *mainNavalLocation;
							break;
						}
					}
				}
			}
		}

		LegacyNavy newLegacyNavy(army.getName(), navalLocation, base);
		MtgNavy newMtgNavy(army.getName(), navalLocation, base);

		for (const auto& regiment: army.getRegiments())
		{
			auto type = regiment->getType();
			if (unitMap.hasMatchingType(type))
			{
				for (const auto& unitInfo: unitMap.getMatchingUnitInfo(type))
				{
					if (unitInfo.getCategory() == "naval" && theShipVariants.hasLegacyVariant(unitInfo.getVersion()))
					{
						LegacyShip newLegacyShip(regiment->getName(), unitInfo.getType(), unitInfo.getEquipment(), tag);
						newLegacyNavy.addShip(newLegacyShip);
					}
				}
			}
			else
			{
				LOG(LogLevel::Warning) << "Unknown legacy unit type: " << type;
			}
			if (mtgUnitMap.hasMatchingType(type))
			{
				for (const auto& unitInfo: mtgUnitMap.getMatchingUnitInfo(type))
				{
					if ((unitInfo.getCategory() == "naval") && theShipVariants.hasMtgVariant(unitInfo.getVersion()))
					{
						auto experience = static_cast<float>(regiment->getExperience() / 100);
						MtgShip newMtgShip(regiment->getName(),
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
				LOG(LogLevel::Warning) << "Unknown mtg unit type: " << type;
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