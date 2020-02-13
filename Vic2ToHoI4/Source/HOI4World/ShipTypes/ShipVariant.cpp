#include "ShipVariant.h"
#include "ParserHelpers.h"



HoI4::shipVariant::shipVariant(std::istream& theStream)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword(std::regex("type"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword(std::regex("name_group"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString nameGroupString(theStream);
		nameGroup = nameGroupString.getString();
	});
	registerKeyword(std::regex("modules"), [this](const std::string& unused, std::istream& theStream){
		modules = std::make_unique<shipModules>(theStream);
	});
	registerKeyword(std::regex("obsolete"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString obsoleteString(theStream);
		obsolete = (obsoleteString.getString() == "yes");
	});
	registerKeyword(std::regex("required_techs"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringList requiredTechsStrings(theStream);
		for (const auto& requiredTech: requiredTechsStrings.getStrings())
		{
			requiredTechnologies.insert(requiredTech);
		}
	});
	registerKeyword(std::regex("blocking_techs"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringList blockingTechsStrings(theStream);
		for (const auto& blockingTech: blockingTechsStrings.getStrings())
		{
			blockingTechnologies.insert(blockingTech);
		}
	});

	parseStream(theStream);
}


HoI4::shipVariant::shipVariant(const shipVariant& source): parser(source)
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


HoI4::shipVariant& HoI4::shipVariant::operator=(const shipVariant& source)
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


void HoI4::shipVariant::setOwningCountryTag(const std::string& tag)
{
	owningCountryTag = tag;
}


bool HoI4::shipVariant::isValidVariant(const technologies& ownedTechs) const
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