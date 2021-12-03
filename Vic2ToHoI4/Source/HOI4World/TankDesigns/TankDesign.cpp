#include "TankDesign.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"


HoI4::TankDesign::TankDesign(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		name = commonItems::singleString(theStream).getString();
	});
	registerKeyword("type", [this](std::istream& theStream) {
		type = commonItems::singleString(theStream).getString();
	});
	registerKeyword("modules", [this](std::istream& theStream) {
		modules = std::make_unique<TankModules>(theStream);
	});
	registerKeyword("upgrades", [this](std::istream& theStream) {
		upgrades = std::make_unique<TankUpgrades>(theStream);
	});
	registerKeyword("icon", [this](std::istream& theStream) {
		icon = commonItems::singleString(theStream).getString();
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


HoI4::TankDesign::TankDesign(const TankDesign& source):
	 parser(source), name(source.name), type(source.type), modules(std::make_unique<TankModules>(*source.modules)),
	 icon(source.icon), obsolete(source.obsolete), requiredTechnologies(source.requiredTechnologies),
	 blockingTechnologies(source.blockingTechnologies)
{
	if (source.upgrades)
	{
		upgrades = std::make_unique<TankUpgrades>(*source.upgrades);
	}
}


bool HoI4::TankDesign::isValidDesign(const technologies& ownedTechs) const
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