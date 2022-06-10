#include "src/HOI4World/Ideologies/Ideology.h"
#include "external/common_items/Color.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Ideologies/IdeologyItems.h"



HoI4::Ideology::Ideology(const std::string& _ideologyName, std::istream& theStream): ideologyName(_ideologyName)
{
	registerKeyword("types", [this](std::istream& theStream) {
		const commonItems::stringsOfItemNames typesStrings(theStream);
		types = typesStrings.getStrings();
	});
	registerKeyword("dynamic_faction_names", [this](std::istream& theStream) {
		const commonItems::stringList namesStrings(theStream);
		dynamicFactionNames = namesStrings.getStrings();
	});
	registerKeyword("color", [this](std::istream& theStream) {
		theColor = commonItems::Color::Factory().getColor(theStream);
	});
	registerKeyword("war_impact_on_world_tension", [this](std::istream& theStream) {
		const commonItems::singleDouble impactNum(theStream);
		warImpactOnWorldTension = static_cast<float>(impactNum.getDouble());
	});
	registerKeyword("faction_impact_on_world_tension", [this](std::istream& theStream) {
		const commonItems::singleDouble impactNum(theStream);
		factionImpactOnWorldTension = static_cast<float>(impactNum.getDouble());
	});
	registerKeyword("rules", [this](std::istream& theStream) {
		IdeologyItems importedRules(theStream);
		rules = importedRules.takeItems();
	});
	registerKeyword("modifiers", [this](std::istream& theStream) {
		IdeologyItems importedModifiers(theStream);
		modifiers = importedModifiers.takeItems();
	});
	registerKeyword("faction_modifiers", [this](std::istream& theStream) {
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
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


HoI4::Ideology::Ideology(const Ideology& other):
	 parser(other), ideologyName(other.ideologyName), types(other.types), dynamicFactionNames(other.dynamicFactionNames),
	 theColor(other.theColor), rules(other.rules), warImpactOnWorldTension(other.warImpactOnWorldTension),
	 factionImpactOnWorldTension(other.factionImpactOnWorldTension), modifiers(other.modifiers),
	 factionModifiers(other.factionModifiers), cans(other.cans), AI(other.AI)
{
}


HoI4::Ideology& HoI4::Ideology::operator=(const Ideology& other)
{
	ideologyName = other.ideologyName;
	types = other.types;
	dynamicFactionNames = other.dynamicFactionNames;
	theColor = other.theColor;
	rules = other.rules;
	warImpactOnWorldTension = other.warImpactOnWorldTension;
	factionImpactOnWorldTension = other.factionImpactOnWorldTension;
	modifiers = other.modifiers;
	factionModifiers = other.factionModifiers;
	cans = other.cans;
	AI = other.AI;

	return *this;
}