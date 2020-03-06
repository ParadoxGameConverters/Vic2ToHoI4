#include "Ideology.h"
#include "../../Color.h"
#include "IdeologyItems.h"
#include "ParserHelpers.h"



HoI4::Ideology::Ideology(const std::string& _ideologyName, std::istream& theStream): ideologyName(_ideologyName)
{
	registerKeyword("types", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringsOfItemNames typesStrings(theStream);
		types = typesStrings.getStrings();
	});
	registerKeyword("dynamic_faction_names", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList namesStrings(theStream);
		dynamicFactionNames = namesStrings.getStrings();
	});
	registerKeyword("color", [this](const std::string& unused, std::istream& theStream) {
		theColor = std::make_unique<ConverterColor::Color>(theStream);
	});
	registerKeyword("war_impact_on_world_tension", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble impactNum(theStream);
		warImpactOnWorldTension = static_cast<float>(impactNum.getDouble());
	});
	registerKeyword("faction_impact_on_world_tension", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble impactNum(theStream);
		factionImpactOnWorldTension = static_cast<float>(impactNum.getDouble());
	});
	registerKeyword("rules", [this](const std::string& unused, std::istream& theStream) {
		IdeologyItems importedRules(theStream);
		rules = importedRules.takeItems();
	});
	registerKeyword("modifiers", [this](const std::string& unused, std::istream& theStream) {
		IdeologyItems importedModifiers(theStream);
		modifiers = importedModifiers.takeItems();
	});
	registerKeyword("faction_modifiers", [this](const std::string& unused, std::istream& theStream) {
		IdeologyItems importedModifiers(theStream);
		factionModifiers = importedModifiers.takeItems();
	});
	registerRegex("ai_[a-z]+", [this](const std::string& aiString, std::istream& theStream) {
		AI = aiString;
		commonItems::ignoreItem(aiString, theStream);
	});
	registerRegex("can_[a-z_]+", [this](const std::string& canString, std::istream& theStream) {
		const commonItems::singleString yesNo(theStream);
		cans.insert(std::make_pair(canString, yesNo.getString()));
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


HoI4::Ideology::Ideology(const Ideology& other):
	 parser(other), ideologyName(other.ideologyName), types(other.types), dynamicFactionNames(other.dynamicFactionNames),
	 theColor(std::make_unique<ConverterColor::Color>(*other.theColor)), rules(other.rules),
	 warImpactOnWorldTension(other.warImpactOnWorldTension),
	 factionImpactOnWorldTension(other.factionImpactOnWorldTension), modifiers(other.modifiers),
	 factionModifiers(other.factionModifiers), cans(other.cans), AI(other.AI)
{
}


HoI4::Ideology& HoI4::Ideology::operator=(const Ideology& other)
{
	ideologyName = other.ideologyName;
	types = other.types;
	dynamicFactionNames = other.dynamicFactionNames;
	theColor = std::make_unique<ConverterColor::Color>(*other.theColor);
	rules = other.rules;
	warImpactOnWorldTension = other.warImpactOnWorldTension;
	factionImpactOnWorldTension = other.factionImpactOnWorldTension;
	modifiers = other.modifiers;
	factionModifiers = other.factionModifiers;
	cans = other.cans;
	AI = other.AI;

	return *this;
}