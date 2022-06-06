#include "GameRules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"



HoI4::GameRules HoI4::GameRules::Parser::parseRulesFile(const std::string& filename)
{
	std::vector<GameRule> rules;

	registerRegex(commonItems::catchallRegex, [&rules](const std::string& ruleKey, std::istream& theStream) {
		const auto rule = GameRule::Parser().parseRule(ruleKey, theStream);
		rules.push_back(rule);
	});
	parseFile(filename);

	return GameRules(rules);
}


void HoI4::GameRules::updateRules()
{
	Log(LogLevel::Info) << "\tUpdating game rules";
	std::regex aiBehaviorRegex{"[A-Z]{3}_ai_behavior"};
	gameRules.erase(std::remove_if(gameRules.begin(),
							  gameRules.end(),
							  [aiBehaviorRegex](auto& rule) {
								  std::smatch matchResults;
								  return std::regex_match(rule.getKey(), matchResults, aiBehaviorRegex);
							  }),
		 gameRules.end());

	std::regex fragmentationStatusRegex{"[a-z]{3}_fragmentation_status"};
	gameRules.erase(std::remove_if(gameRules.begin(),
							  gameRules.end(),
							  [fragmentationStatusRegex](auto& rule) {
								  std::smatch matchResults;
								  return std::regex_match(rule.getKey(), matchResults, fragmentationStatusRegex);
							  }),
		 gameRules.end());

	std::regex colonizationStatusRegex{"[a-z]+_colonization_status"};
	gameRules.erase(std::remove_if(gameRules.begin(),
							  gameRules.end(),
							  [colonizationStatusRegex](auto& rule) {
								  std::smatch matchResults;
								  return std::regex_match(rule.getKey(), matchResults, colonizationStatusRegex);
							  }),
		 gameRules.end());
}