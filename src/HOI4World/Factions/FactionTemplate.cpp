#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Factions/FactionTemplates.h"



HoI4::FactionTemplate::FactionTemplate(const std::string& id, std::istream& theStream): id(std::move(id))
{
	registerKeyword("name", [this](std::istream& theStream) {
		name = commonItems::getString(theStream);
	});
	registerKeyword("icon", [this](std::istream& theStream) {
		icon = commonItems::getString(theStream);
	});
	registerKeyword("manifest", [this](std::istream& theStream) {
		manifest = commonItems::getString(theStream);
	});
	registerKeyword("can_leader_join_other_factions", [this](std::istream& theStream) {
		canLeaderJoinOtherFactions = commonItems::getString(theStream) == "yes";
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		visible = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("available", [this](std::istream& theStream) {
		available = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("goals", [this](std::istream& theStream) {
		goals = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("default_rules", [this](std::istream& theStream) {
		rules = commonItems::stringList(theStream).getStrings();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);
	clearRegisteredKeywords();
}

bool HoI4::FactionTemplate::operator==(const FactionTemplate& other) const
{
	return id == other.id && name == other.name && icon == other.icon && goals == other.goals && rules == other.rules;
}