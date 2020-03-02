#include "HoI4Army.h"
#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "../../V2World/Army.h"
#include "../MilitaryMappings/UnitMappings.h"
#include "../States/HoI4State.h"
#include "DivisionType.h"
#include "Log.h"



bool isWastelandProvince(int provinceNum, const HoI4::States& theStates);
void addAvailableBattalionsAndCompanies(
	 std::map<std::string, std::vector<HoI4::SizedRegiment>>& availableBattalionsAndCompanies,
	 const Vic2::Army& sourceArmy,
	 const HoI4::militaryMappings& theMilitaryMappings,
	 double forceMultiplier);
void addRemainingBattalionsAndCompanies(
	 std::map<std::string, std::vector<HoI4::SizedRegiment>>& remainingBattalionsAndCompanies,
	 const std::map<std::string, std::vector<HoI4::SizedRegiment>>& localBattalionsAndCompanies);

void HoI4::Army::convertArmies(const militaryMappings& theMilitaryMappings,
	 const int backupLocation,
	 const double forceMultiplier,
	 const States& theStates)
{
	std::map<std::string, std::vector<SizedRegiment>> remainingBattalionsAndCompanies;

	for (auto army: sourceArmies)
	{
		auto provinceMapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(army->getLocation());
		if (!provinceMapping || isWastelandProvince(*provinceMapping->begin(), theStates))
		{
			addAvailableBattalionsAndCompanies(remainingBattalionsAndCompanies,
				 *army,
				 theMilitaryMappings,
				 forceMultiplier);
			continue;
		}
		std::map<std::string, std::vector<SizedRegiment>> localBattalionsAndCompanies;
		addAvailableBattalionsAndCompanies(localBattalionsAndCompanies, *army, theMilitaryMappings, forceMultiplier);

		convertArmyDivisions(theMilitaryMappings, localBattalionsAndCompanies, *provinceMapping->begin());
		addRemainingBattalionsAndCompanies(remainingBattalionsAndCompanies, localBattalionsAndCompanies);
	}

	convertArmyDivisions(theMilitaryMappings, remainingBattalionsAndCompanies, backupLocation);
}


bool isWastelandProvince(const int provinceNum, const HoI4::States& theStates)
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


void addAvailableBattalionsAndCompanies(
	 std::map<std::string, std::vector<HoI4::SizedRegiment>>& availableBattalionsAndCompanies,
	 const Vic2::Army& sourceArmy,
	 const HoI4::militaryMappings& theMilitaryMappings,
	 const double forceMultiplier)
{
	for (auto regiment: sourceArmy.getRegiments())
	{
		auto Vic2Type = regiment->getType();

		if (theMilitaryMappings.getUnitMappings().hasMatchingType(Vic2Type))
		{
			auto unitInfo = theMilitaryMappings.getUnitMappings().getMatchingUnitInfo(Vic2Type);

			if (unitInfo && unitInfo->getCategory() == "land")
			{
				HoI4::SizedRegiment theRegiment;
				theRegiment.unitSize = unitInfo->getSize() * forceMultiplier;
				theRegiment.regiment = regiment;
				availableBattalionsAndCompanies[unitInfo->getType()].push_back(theRegiment);
			}
		}
		else
		{
			LOG(LogLevel::Warning) << "Unknown unit type: " << Vic2Type;
		}
	}
}


void addRemainingBattalionsAndCompanies(
	 std::map<std::string, std::vector<HoI4::SizedRegiment>>& remainingBattalionsAndCompanies,
	 const std::map<std::string, std::vector<HoI4::SizedRegiment>>& localBattalionsAndCompanies)
{
	for (const auto& unit: localBattalionsAndCompanies)
	{
		std::vector<HoI4::SizedRegiment> remainingRegiments;
		for (auto regiment: unit.second)
		{
			if (regiment.unitSize > 0)
			{
				remainingRegiments.push_back(regiment);
			}
		}

		if (auto remainingUnit = remainingBattalionsAndCompanies.find(unit.first);
			 remainingUnit != remainingBattalionsAndCompanies.end())
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


std::map<std::string, int> determineTemplateRequirements(const HoI4::DivisionTemplateType& divisionTemplate);
bool sufficientUnits(const std::map<std::string, std::vector<HoI4::SizedRegiment>>& units,
	 const std::map<std::string, std::string>& substitutes,
	 const std::map<std::string, int>& requiredUnits);
HoI4::DivisionType createDivision(const std::map<std::string, int>& templateRequirements,
	 std::map<std::string, std::vector<HoI4::SizedRegiment>>& BattalionsAndCompanies,
	 const HoI4::militaryMappings& theMilitaryMappings,
	 int divisionCounter,
	 const HoI4::DivisionTemplateType& divisionTemplate,
	 int location);

void HoI4::Army::convertArmyDivisions(const militaryMappings& theMilitaryMappings,
	 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
	 const int location)
{
	for (const auto& divisionTemplate: theMilitaryMappings.getDivisionTemplates())
	{
		auto templateRequirements = determineTemplateRequirements(divisionTemplate);

		auto divisionCounter = 1;
		while (sufficientUnits(BattalionsAndCompanies, theMilitaryMappings.getSubstitutes(), templateRequirements))
		{
			divisions.push_back(createDivision(templateRequirements,
				 BattalionsAndCompanies,
				 theMilitaryMappings,
				 divisionCounter,
				 divisionTemplate,
				 location));
			divisionCounter++;
		}
	}
}


std::map<std::string, int> determineTemplateRequirements(const HoI4::DivisionTemplateType& divisionTemplate)
{
	std::map<std::string, int> templateRequirements;
	for (const auto& regiment: divisionTemplate.getRegiments())
	{
		templateRequirements[regiment.getType()] = templateRequirements[regiment.getType()] + 1;
	}
	for (const auto& regiment: divisionTemplate.getSupportRegiments())
	{
		templateRequirements[regiment.getType()] = templateRequirements[regiment.getType()] + 1;
	}

	return templateRequirements;
}


bool sufficientUnits(const std::map<std::string, std::vector<HoI4::SizedRegiment>>& units,
	 const std::map<std::string, std::string>& substitutes,
	 const std::map<std::string, int>& requiredUnits)
{
	for (const auto& requiredUnit: requiredUnits)
	{
		double available = 0;

		if (auto unit = units.find(requiredUnit.first); unit != units.end())
		{
			for (auto sizedRegiment: unit->second)
			{
				available += sizedRegiment.unitSize;
			}
		}
		if (auto substitute = substitutes.find(requiredUnit.first); substitute != substitutes.end())
		{
			if (auto unit = units.find(substitute->second); unit != units.end())
			{
				for (auto sizedRegiment: unit->second)
				{
					available += sizedRegiment.unitSize;
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


HoI4::DivisionType createDivision(const std::map<std::string, int>& templateRequirements,
	 std::map<std::string, std::vector<HoI4::SizedRegiment>>& BattalionsAndCompanies,
	 const HoI4::militaryMappings& theMilitaryMappings,
	 const int divisionCounter,
	 const HoI4::DivisionTemplateType& divisionTemplate,
	 const int location)
{
	auto totalExperience = 0.0;
	auto totalRequirement = 0.0;
	for (const auto& requirement: templateRequirements)
	{
		totalRequirement += requirement.second;
		double remainingRequirement = requirement.second;
		for (auto& regiment: BattalionsAndCompanies[requirement.first])
		{
			if (regiment.unitSize > 0)
			{
				const auto decreaseAmount = std::min(regiment.unitSize, remainingRequirement);
				regiment.unitSize -= decreaseAmount;
				remainingRequirement -= decreaseAmount;

				totalExperience += decreaseAmount * regiment.regiment->getExperience();
			}
		}
		if (const auto& substitutes = theMilitaryMappings.getSubstitutes();
			 substitutes.count(requirement.first) && BattalionsAndCompanies.count(substitutes.at(requirement.first)))
		{
			for (auto& regiment: BattalionsAndCompanies[theMilitaryMappings.getSubstitutes().at(requirement.first)])
			{
				if (regiment.unitSize > 0)
				{
					const auto decreaseAmount = std::min(regiment.unitSize, remainingRequirement);
					regiment.unitSize -= decreaseAmount;
					remainingRequirement -= decreaseAmount;

					totalExperience += decreaseAmount * regiment.regiment->getExperience();
				}
			}
		}
	}

	auto actualExperience = totalExperience / totalRequirement / 100.0;
	if (actualExperience > 1.0)
	{
		actualExperience = 1.0;
	}

	return HoI4::DivisionType(std::to_string(divisionCounter) + ". " + divisionTemplate.getName(),
		 divisionTemplate.getName(),
		 location,
		 actualExperience);
}