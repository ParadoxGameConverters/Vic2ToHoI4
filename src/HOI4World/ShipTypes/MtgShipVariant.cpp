#include "MtgShipVariant.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::MtgShipVariant::MtgShipVariant(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("type", [this](std::istream& theStream) {
		const commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword("name_group", [this](std::istream& theStream) {
		const commonItems::singleString nameGroupString(theStream);
		nameGroup = nameGroupString.getString();
	});
	registerKeyword("modules", [this](std::istream& theStream) {
		modules = std::make_unique<shipModules>(theStream);
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


HoI4::MtgShipVariant::MtgShipVariant(const MtgShipVariant& source): parser(source)
{
	name = source.name;
	type = source.type;
	owningCountryTag = source.owningCountryTag;
	nameGroup = source.nameGroup;
	modules = std::make_unique<shipModules>(*source.modules);
	obsolete = source.obsolete;
	ownerTag = source.ownerTag;
	requiredTechnologies = source.requiredTechnologies;
	blockingTechnologies = source.blockingTechnologies;
}


HoI4::MtgShipVariant& HoI4::MtgShipVariant::operator=(const MtgShipVariant& source)
{
	name = source.name;
	type = source.type;
	owningCountryTag = source.owningCountryTag;
	nameGroup = source.nameGroup;
	modules = std::make_unique<shipModules>(*source.modules);
	obsolete = source.obsolete;
	ownerTag = source.ownerTag;
	requiredTechnologies = source.requiredTechnologies;
	blockingTechnologies = source.blockingTechnologies;

	return *this;
}


void HoI4::MtgShipVariant::setOwningCountryTag(const std::string& tag)
{
	owningCountryTag = tag;
}


bool HoI4::MtgShipVariant::isValidVariant(const technologies& ownedTechs) const
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