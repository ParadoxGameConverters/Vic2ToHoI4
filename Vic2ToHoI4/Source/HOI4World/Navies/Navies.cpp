/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "Navies.h"
#include "../../Mappers/ProvinceDefinitions.h"
#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "Log.h"



HoI4::Navies::Navies(
	std::vector<const Vic2::Army*> srcArmies,
	int backupNavalLocation,
	const UnitMappings& unitMap,
	const MtgUnitMappings& mtgUnitMap,
	const HoI4::shipVariants& theShipVariants,
	const HoI4::coastalProvinces& theCoastalProvinces,
	const std::map<int, int>& provinceToStateIDMap,
	std::map<int, HoI4::State> states,
	const std::string& tag)
{
	for (auto army: srcArmies)
	{
		int navalLocation = backupNavalLocation;
		int base = backupNavalLocation;

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
				else
				{
					if (provinceToStateIDMap.find(possibleProvince) != provinceToStateIDMap.end())
					{
						int stateID = provinceToStateIDMap.at(possibleProvince);
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
		}

		HoI4::LegacyNavy newLegacyNavy(army->getName(), navalLocation, base);
		HoI4::MtgNavy newMtgNavy(army->getName(), navalLocation, base);

		for (auto regiment : army->getRegiments())
		{
			std::string type = regiment->getType();
			if (unitMap.hasMatchingType(type))
			{
				if (auto unitInfo = unitMap.getMatchingUnitInfo(type); unitInfo && unitInfo->getCategory() == "naval")
				{
					HoI4::LegacyShip newLegacyShip(
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
				std::vector<HoI4::HoI4UnitType> unitInfos = mtgUnitMap.getMatchingUnitInfo(type);
				for (auto unitInfo: unitInfos)
				{
					if ((unitInfo.getCategory() == "naval") && theShipVariants.hasVariant(unitInfo.getVersion()))
					{
						float experience = static_cast<float>(regiment->getExperience() / 100);
						HoI4::MtgShip newMtgShip(regiment->getName(), unitInfo.getType(), unitInfo.getEquipment(), tag, unitInfo.getVersion(), experience);
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