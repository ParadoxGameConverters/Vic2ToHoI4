#include "Navies.h"
#include "../../Mappers/ProvinceDefinitions.h"
#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "Log.h"



HoI4::Navies::Navies(
	const std::vector<const Vic2::Army*>& srcArmies,
	int backupNavalLocation,
	const UnitMappings& unitMap,
	const MtgUnitMappings& mtgUnitMap,
	const shipVariants& theShipVariants,
	const std::map<int, int>& provinceToStateIDMap,
	std::map<int, State> states,
	const std::string& tag)
{
	for (auto army: srcArmies)
	{
		auto navalLocation = backupNavalLocation;
		auto base = backupNavalLocation;

		auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(army->getLocation());
		if (mapping)
		{
			for (auto possibleProvince: *mapping)
			{
				if (provinceDefinitions::isSeaProvince(possibleProvince))
				{
					navalLocation = possibleProvince;
					break;
				}
				else if (provinceToStateIDMap.find(possibleProvince) != provinceToStateIDMap.end())
				{
					auto stateID = provinceToStateIDMap.at(possibleProvince);
					if (states.find(stateID) != states.end())
					{
						auto state = states.at(stateID);
						auto mainNavalLocation = state.getMainNavalLocation();
						if (mainNavalLocation)
						{
							navalLocation = *mainNavalLocation;
							base = *mainNavalLocation;
							break;
						}
					}
				}
			}
		}

		LegacyNavy newLegacyNavy(army->getName(), navalLocation, base);
		MtgNavy newMtgNavy(army->getName(), navalLocation, base);

		for (auto regiment : army->getRegiments())
		{
			auto type = regiment->getType();
			if (unitMap.hasMatchingType(type))
			{
				if (auto unitInfo = unitMap.getMatchingUnitInfo(type); unitInfo && unitInfo->getCategory() == "naval")
				{
					LegacyShip newLegacyShip(
						regiment->getName(),
						unitInfo->getType(),
						unitInfo->getEquipment(),
						tag
					);
					newLegacyNavy.addShip(newLegacyShip);
				}
			}
			else
			{
				LOG(LogLevel::Warning) << "Unknown legacy unit type: " << type;
			}
			if (mtgUnitMap.hasMatchingType(type))
			{
				auto unitInfos = mtgUnitMap.getMatchingUnitInfo(type);
				for (const auto& unitInfo: unitInfos)
				{
					if ((unitInfo.getCategory() == "naval") && theShipVariants.hasVariant(unitInfo.getVersion()))
					{
						auto experience = static_cast<float>(regiment->getExperience() / 100);
						MtgShip newMtgShip(regiment->getName(), unitInfo.getType(), unitInfo.getEquipment(), tag, unitInfo.getVersion(), experience);
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