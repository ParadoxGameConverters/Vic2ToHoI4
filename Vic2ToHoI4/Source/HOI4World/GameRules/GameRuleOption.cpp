#include "GameRuleOption.h"
#include "ParserHelpers.h"



HoI4::GameRuleOption HoI4::GameRuleOption::Parser::parseOption(std::istream& theStream)
{
	std::string name;
	std::string text;
	std::string description;
	std::optional<bool> allowAchievements;

	registerKeyword("name", [&name](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("text", [&text](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString textString(theStream);
		text = textString.getString();
	});
	registerKeyword("desc", [&description](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString descriptionString(theStream);
		description = descriptionString.getString();
	});
	registerKeyword("allow_achievements", [&allowAchievements](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString allowString(theStream);
		allowAchievements = allowString.getString() == "yes";
	});
	parseStream(theStream);

	return GameRuleOption(name, text, description, allowAchievements);
}