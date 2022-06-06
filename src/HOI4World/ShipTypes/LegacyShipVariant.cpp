#include "LegacyShipVariant.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "ShipUpgrades.h"



HoI4::LegacyShipVariant::LegacyShipVariant(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("type", [this](std::istream& theStream) {
		const commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword("upgrades", [this](std::istream& theStream) {
		ShipUpgrades importedUpgrades(theStream);
		upgrades = importedUpgrades.takeUpgrades();
	});
	registerKeyword("obsolete", [this](std::istream& theStream) {
		const commonItems::singleString obsoleteString(theStream);
		obsolete = (obsoleteString.getString() == "yes");
	});
	registerKeyword("required_techs", [this](std::istream& theStream) {
		const commonItems::stringList requiredTechsStrings(theStream);
		for (const auto& requiredTech: requiredTechsStrings.getStrings())
		{
			requiredTechnologies.insert(requiredTech);
		}
	});
	registerKeyword("blocking_techs", [this](std::istream& theStream) {
		const commonItems::stringList blockingTechsStrings(theStream);
		for (const auto& blockingTech: blockingTechsStrings.getStrings())
		{
			blockingTechnologies.insert(blockingTech);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


bool HoI4::LegacyShipVariant::isValidVariant(const technologies& ownedTechs) const
{
	for (const auto& requiredTechnology: requiredTechnologies)
	{
		if (!ownedTechs.hasTechnology(requiredTechnology))
		{
			return false;
		}
	}

	for (const auto& blockingTechnology: blockingTechnologies)
	{
		if (ownedTechs.hasTechnology(blockingTechnology))
		{
			return false;
		}
	}

	return true;
}
