#include "HoI4Army.h"
#include "DivisionType.h"
#include "HOI4World/MilitaryMappings/UnitMappings.h"
#include "HOI4World/States/HoI4State.h"
#include "Log.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "V2World/Military/Army.h"



namespace HoI4
{

bool isWastelandProvince(int provinceNum, const States& theStates);
void addAvailableBattalionsAndCompanies(
	 std::map<std::string, std::vector<SizedRegiment>>& availableBattalionsAndCompanies,
	 const Vic2::Army& sourceArmy,
	 const militaryMappings& theMilitaryMappings,
	 double forceMultiplier);
void addRemainingBattalionsAndCompanies(
	 std::map<std::string, std::vector<SizedRegiment>>& remainingBattalionsAndCompanies,
	 const std::map<std::string, std::vector<SizedRegiment>>& localBattalionsAndCompanies);
std::map<std::string, int> determineTemplateRequirements(const DivisionTemplateType& divisionTemplate);
bool sufficientUnits(const std::map<std::string, std::vector<SizedRegiment>>& units,
	 const std::map<std::string, std::string>& substitutes,
	 const std::map<std::string, int>& requiredUnits);
DivisionType createDivision(const std::map<std::string, int>& templateRequirements,
	 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
	 const militaryMappings& theMilitaryMappings,
	 int divisionCounter,
	 const DivisionTemplateType& divisionTemplate,
	 int location);

} // namespace HoI4


void HoI4::Army::convertArmies(const militaryMappings& theMilitaryMappings,
	 const int backupLocation,
	 const double forceMultiplier,
	 const technologies& countryTechnologies,
	 const States& theStates,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	std::map<std::string, std::vector<SizedRegiment>> remainingBattalionsAndCompanies;

	for (const auto& army: sourceArmies)
	{
		auto location = getLocation(army.getLocation(), provinceMapper);
		if (!location || isWastelandProvince(*location, theStates))
		{
			addAvailableBattalionsAndCompanies(remainingBattalionsAndCompanies,
				 army,
				 theMilitaryMappings,
				 forceMultiplier);
			continue;
		}
		std::map<std::string, std::vector<SizedRegiment>> localBattalionsAndCompanies;
		addAvailableBattalionsAndCompanies(localBattalionsAndCompanies, army, theMilitaryMappings, forceMultiplier);
		const auto divisionsBefore = divisions.size();

		convertArmyDivisions(theMilitaryMappings, localBattalionsAndCompanies, countryTechnologies, *location);
		if (divisionsBefore != divisions.size())
		{
			divisionLocations.insert(*location);
		}

		addRemainingBattalionsAndCompanies(remainingBattalionsAndCompanies, localBattalionsAndCompanies);
	}

	if (!remainingBattalionsAndCompanies.empty())
	{
		divisionLocations.insert(backupLocation);
	}
	convertArmyDivisions(theMilitaryMappings, remainingBattalionsAndCompanies, countryTechnologies, backupLocation);

	collectLeftoverEquipment(remainingBattalionsAndCompanies);
}


std::optional<int> HoI4::Army::getLocation(std::optional<int> vic2Location,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	if (vic2Location == std::nullopt)
	{
		return std::nullopt;
	}

	const auto mapping = provinceMapper.getVic2ToHoI4ProvinceMapping(*vic2Location);
	if (mapping.empty())
	{
		return std::nullopt;
	}

	return mapping[0];
}


bool HoI4::isWastelandProvince(const int provinceNum, const States& theStates)
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


void HoI4::addAvailableBattalionsAndCompanies(
	 std::map<std::string, std::vector<SizedRegiment>>& availableBattalionsAndCompanies,
	 const Vic2::Army& sourceArmy,
	 const militaryMappings& theMilitaryMappings,
	 const double forceMultiplier)
{
	for (const auto& regiment: sourceArmy.getUnits())
	{
		auto Vic2Type = regiment.getType();

		if (theMilitaryMappings.getUnitMappings().hasMatchingType(Vic2Type))
		{
			for (const auto& unitInfo: theMilitaryMappings.getUnitMappings().getMatchingUnitInfo(Vic2Type))
			{
				if (unitInfo.getCategory() == "land")
				{
					SizedRegiment theRegiment;
					theRegiment.unitSize = unitInfo.getSize() * forceMultiplier;
					theRegiment.experience = regiment.getExperience();
					theRegiment.strength = regiment.getStrength();
					availableBattalionsAndCompanies[unitInfo.getType()].push_back(theRegiment);
					break;
				}
			}
		}
		else
		{
			Log(LogLevel::Warning) << "Unknown unit type: " << Vic2Type;
		}
	}
}


void HoI4::addRemainingBattalionsAndCompanies(
	 std::map<std::string, std::vector<SizedRegiment>>& remainingBattalionsAndCompanies,
	 const std::map<std::string, std::vector<SizedRegiment>>& localBattalionsAndCompanies)
{
	for (const auto& unit: localBattalionsAndCompanies)
	{
		std::vector<SizedRegiment> remainingRegiments;
		for (const auto& regiment: unit.second)
		{
			if (regiment.unitSize > 0)
			{
				remainingRegiments.push_back(regiment);
			}
		}

		if (auto remainingUnit = remainingBattalionsAndCompanies.find(unit.first);
			 remainingUnit != remainingBattalionsAndCompanies.end())
		{
			for (const auto& regiment: remainingRegiments)
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


void HoI4::Army::convertArmyDivisions(const militaryMappings& theMilitaryMappings,
	 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
	 const technologies& countryTechnologies,
	 const int location)
{
	for (const auto& divisionTemplate: theMilitaryMappings.getDivisionTemplates())
	{
		if (missingRequiredTechnologies(divisionTemplate, countryTechnologies))
		{
			continue;
		}

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


bool HoI4::Army::missingRequiredTechnologies(const DivisionTemplateType& divisionTemplate,
	 const technologies& countryTechnologies)
{
	for (const auto& requiredTechnology: divisionTemplate.getRequiredTechnologies())
	{
		if (!countryTechnologies.hasTechnology(requiredTechnology))
		{
			return true;
		}
	}

	return false;
}


std::map<std::string, int> HoI4::determineTemplateRequirements(const DivisionTemplateType& divisionTemplate)
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


bool HoI4::sufficientUnits(const std::map<std::string, std::vector<SizedRegiment>>& units,
	 const std::map<std::string, std::string>& substitutes,
	 const std::map<std::string, int>& requiredUnits)
{
	for (const auto& requiredUnit: requiredUnits)
	{
		double available = 0;

		if (auto unit = units.find(requiredUnit.first); unit != units.end())
		{
			for (const auto& sizedRegiment: unit->second)
			{
				available += sizedRegiment.unitSize;
			}
		}
		if (auto substitute = substitutes.find(requiredUnit.first); substitute != substitutes.end())
		{
			if (auto unit = units.find(substitute->second); unit != units.end())
			{
				for (const auto& sizedRegiment: unit->second)
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


HoI4::DivisionType HoI4::createDivision(const std::map<std::string, int>& templateRequirements,
	 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
	 const militaryMappings& theMilitaryMappings,
	 const int divisionCounter,
	 const DivisionTemplateType& divisionTemplate,
	 const int location)
{
	auto totalExperience = 0.0;
	auto totalStrength = 0.0;
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

				totalExperience += decreaseAmount * regiment.experience;
				totalStrength += decreaseAmount * regiment.strength;
			}
		}
		if (const auto& substitutes = theMilitaryMappings.getSubstitutes();
			 substitutes.contains(requirement.first) && BattalionsAndCompanies.contains(substitutes.at(requirement.first)))
		{
			for (auto& regiment: BattalionsAndCompanies[theMilitaryMappings.getSubstitutes().at(requirement.first)])
			{
				if (regiment.unitSize > 0)
				{
					const auto decreaseAmount = std::min(regiment.unitSize, remainingRequirement);
					regiment.unitSize -= decreaseAmount;
					remainingRequirement -= decreaseAmount;

					totalExperience += decreaseAmount * regiment.experience;
					totalStrength += decreaseAmount * regiment.strength;
				}
			}
		}
	}

	auto actualExperience = totalExperience / totalRequirement / 100.0;
	auto actualStrength = totalStrength / totalRequirement / 3.0;
	if (actualExperience > 1.0)
	{
		actualExperience = 1.0;
	}

	return DivisionType(std::to_string(divisionCounter) + ". " + divisionTemplate.getName(),
		 divisionTemplate.getName(),
		 location,
		 actualExperience,
		 actualStrength);
}


void HoI4::Army::collectLeftoverEquipment(std::map<std::string, std::vector<SizedRegiment>>& battalionsAndCompanies)
{
	for (const auto& [type, sizedRegiment]: battalionsAndCompanies)
	{
		for (const auto& regiment: sizedRegiment)
		{
			// TODO(#737): Make this use the HoI4 data instead of hard-coding
			if (type == "infantry")
			{
				leftoverEquipment["infantry_equipment_0"] += static_cast<int>(regiment.unitSize * 100);
			}
			else if (type == "cavalry")
			{
				leftoverEquipment["infantry_equipment_0"] += static_cast<int>(regiment.unitSize * 120);
			}
			else if (type == "artillery_brigade")
			{
				leftoverEquipment["artillery_equipment_1"] += static_cast<int>(regiment.unitSize * 12);
			}
			else if (type == "light_armor")
			{
				leftoverEquipment["gw_tank_equipment"] += static_cast<int>(regiment.unitSize * 60);
			}
		}
	}
}