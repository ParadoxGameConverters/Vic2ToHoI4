#include "GameRuleOption.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::GameRuleOption HoI4::GameRuleOption::Parser::parseOption(const std::string& key, std::istream& theStream)
{
	std::string name;
	std::string text;
	std::string description;
	std::optional<bool> allowAchievements;

	registerKeyword("name", [&name](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("text", [&text](std::istream& theStream) {
		const commonItems::singleString textString(theStream);
		text = textString.getString();
	});
	registerKeyword("desc", [&description](std::istream& theStream) {
		const commonItems::singleString descriptionString(theStream);
		description = descriptionString.getString();
	});
	registerKeyword("allow_achievements", [&allowAchievements](std::istream& theStream) {
		const commonItems::singleString allowString(theStream);
		allowAchievements = allowString.getString() == "yes";
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);

	return GameRuleOption(key == "default", name, text, description, allowAchievements);
}