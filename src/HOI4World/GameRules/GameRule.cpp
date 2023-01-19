#include "src/HOI4World/GameRules/GameRule.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::GameRule HoI4::GameRule::Parser::parseRule(const std::string& key, std::istream& theStream)
{
	std::string name;
	std::optional<std::string> requiredDlc;
	std::string group;
	std::optional<std::string> icon;
	std::vector<GameRuleOption> options;

	registerKeyword("name", [&name](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("required_dlc", [&requiredDlc](std::istream& theStream) {
		const commonItems::singleString dlcString(theStream);
		requiredDlc = dlcString.getString();
	});
	registerKeyword("group", [&group](std::istream& theStream) {
		const commonItems::singleString groupString(theStream);
		group = groupString.getString();
	});
	registerKeyword("icon", [&icon](std::istream& theStream) {
		const commonItems::singleString iconString(theStream);
		icon = iconString.getString();
	});
	registerRegex("option|default", [&options](const std::string& key, std::istream& theStream) {
		const auto option = GameRuleOption::Parser().parseOption(key, theStream);
		options.push_back(option);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);

	return GameRule(key, name, requiredDlc, group, icon, options);
}