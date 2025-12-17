#ifndef FACTION_RULE_GROUPS_H
#define FACTION_RULE_GROUPS_H



#include "external/common_items/Parser.h"



namespace HoI4
{

class FactionRuleGroups: commonItems::parser
{
  public:
	FactionRuleGroups(const std::filesystem::path& hoi4Path);
	FactionRuleGroups(std::istream& theStream);

	[[nodiscard]] const auto& getRuleGroups() const { return ruleGroups; }
	[[nodiscard]] const auto& getRules() const { return rules; }

	void removeRule(const std::string& ruleId);

  private:
	std::map<std::string, std::vector<std::string>> ruleGroups;
	std::vector<std::string> rules;
};


} // namespace HoI4



#endif // FACTION_RULE_GROUPS_H