#include "GameRules.h"



HoI4::GameRules HoI4::GameRules::Parser::parseRulesFile(const std::string& filename)
{
	std::vector<GameRule> rules;

	registerRegex("[a-zA-Z0-9_]+", [&rules](const std::string& ruleKey, std::istream& theStream) {
		const GameRule rule = GameRule::Parser{}.parseRule(ruleKey, theStream);
		rules.push_back(rule);
	});

	parseFile(filename);

	return GameRules(rules);
}