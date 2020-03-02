#include "HoI4Army.h"
#include "DivisionType.h"
#include "../MilitaryMappings/UnitMappings.h"
#include "../States/HoI4State.h"
#include "../../Configuration.h"
#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "../../V2World/Army.h"
#include "Log.h"



void HoI4::Army::convertArmies(
	const militaryMappings& theMilitaryMappings,
	int backupLocation,
	double forceMultiplier,
	const HoI4::States& theStates
)
{
	std::map<std::string, std::vector<sizedRegiment>> remainingBattalionsAndCompanies;

	for (auto army: sourceArmies)
	{
		auto provinceMapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(army->getLocation());
		if (!provinceMapping || isWastelandProvince(*provinceMapping->begin(), theStates))
		{
			for (auto regiment : army->getRegiments())
			{
				std::string Vic2Type = regiment->getType();

				if (theMilitaryMappings.getUnitMappings().hasMatchingType(Vic2Type))
				{
					auto unitInfo = theMilitaryMappings.getUnitMappings().getMatchingUnitInfo(Vic2Type);

					if (unitInfo && unitInfo->getCategory() == "land")
					{
						// Calculate how many Battalions and Companies are available after mapping Vic2 armies
						sizedRegiment theRegiment;
						theRegiment.unitSize = unitInfo->getSize() * forceMultiplier;
						theRegiment.regiment = regiment;
						remainingBattalionsAndCompanies[unitInfo->getType()].push_back(theRegiment);
					}
				}
				else
				{
					LOG(LogLevel::Warning) << "Unknown unit type: " << Vic2Type;
				}
			}
			continue;
		}

		std::map<std::string, std::vector<sizedRegiment>> localBattalionsAndCompanies;
		for (auto regiment: army->getRegiments())
		{
			std::string Vic2Type = regiment->getType();

			if (theMilitaryMappings.getUnitMappings().hasMatchingType(Vic2Type))
			{
				auto unitInfo = theMilitaryMappings.getUnitMappings().getMatchingUnitInfo(Vic2Type);

				if (unitInfo && unitInfo->getCategory() == "land")
				{
					// Calculate how many Battalions and Companies are available after mapping Vic2 armies
					sizedRegiment theRegiment;
					theRegiment.unitSize = unitInfo->getSize() * forceMultiplier;
					theRegiment.regiment = regiment;
					localBattalionsAndCompanies[unitInfo->getType()].push_back(theRegiment);
				}
			}
			else
			{
				LOG(LogLevel::Warning) << "Unknown unit type: " << Vic2Type;
			}
		}

		convertArmyDivisions(theMilitaryMappings, localBattalionsAndCompanies, *provinceMapping->begin());
		for (auto unit: localBattalionsAndCompanies)
		{
			std::vector<sizedRegiment> remainingRegiments;
			for (auto regiment: unit.second)
			{
				if (regiment.unitSize > 0)
				{
					remainingRegiments.push_back(regiment);
				}
			}
			auto remainingUnit = remainingBattalionsAndCompanies.find(unit.first);
			if (remainingUnit != remainingBattalionsAndCompanies.end())
			{
				for (auto regiment: remainingRegiments)
				{
					remainingUnit->second.push_back(regiment);
				}
			}
			else
			{
				remainingBattalionsAndCompanies.insert(make_pair(unit.first, remainingRegiments));
			}
		}
	}

	convertArmyDivisions(theMilitaryMappings, remainingBattalionsAndCompanies, backupLocation);
}


void HoI4::Army::convertArmyDivisions(const militaryMappings& theMilitaryMappings, std::map<std::string, std::vector<sizedRegiment>>& BattalionsAndCompanies, int location)
{
	for (auto divTemplate: theMilitaryMappings.getDivisionTemplates())
	{
		// For each template determine the Battalion and Company requirements.
		int divisionCounter = 1;

		std::map<std::string, int> templateRequirements;
		for (auto regiment : divTemplate.getRegiments())
		{
			templateRequirements[regiment.getType()] = templateRequirements[regiment.getType()] + 1;
		}
		for (auto regiment : divTemplate.getSupportRegiments())
		{
			templateRequirements[regiment.getType()] = templateRequirements[regiment.getType()] + 1;
		}

		// Create new divisions as long as sufficient Victoria units exist, otherwise move on to next template.
		while (sufficientUnits(BattalionsAndCompanies, theMilitaryMappings.getSubstitutes(), templateRequirements))
		{
			double totalExperience = 0.0;
			double totalRequirement = 0.0;
			for (auto requirement: templateRequirements)
			{
				totalRequirement += requirement.second;
				double remainingRequirement = requirement.second;
				for (auto& regiment: BattalionsAndCompanies[requirement.first])
				{
					if (regiment.unitSize > 0)
					{
						auto decreaseAmount = std::min(regiment.unitSize, remainingRequirement);
						regiment.unitSize -= decreaseAmount;
						remainingRequirement -= decreaseAmount;

						totalExperience += decreaseAmount * regiment.regiment->getExperience();
					}
				}
				if (const auto& substitutes = theMilitaryMappings.getSubstitutes();
					(
						substitutes.count(requirement.first)) &&
						BattalionsAndCompanies.count(substitutes.at(requirement.first))
					)
				{
					for (auto& regiment: BattalionsAndCompanies[theMilitaryMappings.getSubstitutes().at(requirement.first)])
					{
						if (regiment.unitSize > 0)
						{
							auto decreaseAmount = std::min(regiment.unitSize, remainingRequirement);
							regiment.unitSize -= decreaseAmount;
							remainingRequirement -= decreaseAmount;

							totalExperience += decreaseAmount * regiment.regiment->getExperience();
						}
					}
				}
			}

			double actualExperience = totalExperience / totalRequirement / 100.0;
			if (actualExperience > 1.0)
			{
				actualExperience = 1.0;
			}
			HoI4::DivisionType newDivision(std::to_string(divisionCounter) + ". " + divTemplate.getName(), divTemplate.getName(), location, actualExperience);
			divisionCounter++;
			divisions.push_back(newDivision);
		}
	}
}


bool HoI4::Army::sufficientUnits(const std::map<std::string, std::vector<sizedRegiment>>& units, const std::map<std::string, std::string>& substitutes, const std::map<std::string, int>& requiredUnits)
{
	for (auto requiredUnit: requiredUnits)
	{
		double available = 0;
		if (units.find(requiredUnit.first) != units.end())
		{
			for (auto unit: units.at(requiredUnit.first))
			{
				available += unit.unitSize;
			}
		}
		if (substitutes.find(requiredUnit.first) != substitutes.end())
		{
			if (units.find(substitutes.at(requiredUnit.first)) != units.end())
			{
				for (auto unit: units.at(substitutes.at(requiredUnit.first)))
				{
					available += unit.unitSize;
				}
			}
		}
		if (available < requiredUnit.second)
		{
			return false;
		}
	}

	return true;
}


bool HoI4::Army::isWastelandProvince(int provinceNum, const HoI4::States& theStates)
{
	auto provinceToStateIDMap = theStates.getProvinceToStateIDMap();
	if (const auto& stateNum = provinceToStateIDMap.find(provinceNum); stateNum != provinceToStateIDMap.end())
	{
		const auto& states = theStates.getStates();
		if (const auto& state = states.find(stateNum->second); state != states.end())
		{
			return state->second.getCategory() == "wasteland";
		}
	}

	return true;
}


std::ostream& HoI4::operator << (std::ostream& output, const HoI4::Army& theArmy)
{
	for (auto& division: theArmy.divisions)
	{
		output << division;
	}

	return output;
}