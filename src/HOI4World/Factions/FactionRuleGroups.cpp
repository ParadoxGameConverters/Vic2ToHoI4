#include "src/HOI4World/Factions/FactionRuleGroups.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::FactionRuleGroups::FactionRuleGroups(const std::filesystem::path& hoi4Path)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ruleGroupId, std::istream& theStream) {
		const FactionRuleGroups& ruleGroup(theStream);
		for (const auto& rule: ruleGroup.rules)
		{
			ruleGroups[ruleGroupId].push_back(rule);
		}
	});
	parseFile(hoi4Path / "common/factions/rules/groups/rule_groups.txt");
}


HoI4::FactionRuleGroups::FactionRuleGroups(std::istream& theStream)
{
	registerKeyword("rules", [this](const std::string& unused, std::istream& theStream) {
		rules = commonItems::stringList(theStream).getStrings();
	});
	parseStream(theStream);
}


void HoI4::FactionRuleGroups::removeRule(const std::string& ruleId)
{
	for (auto& [groupId, rules]: ruleGroups)
	{
		std::erase(rules, ruleId);
	}
}