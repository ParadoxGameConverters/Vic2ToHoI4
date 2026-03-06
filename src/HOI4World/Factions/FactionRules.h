#ifndef FACTION_RULES_H
#define FACTION_RULES_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/Factions/FactionRule.h"
#include "src/HOI4World/Factions/FactionRuleGroups.h"



namespace HoI4
{

class FactionRules: commonItems::parser
{
  public:
	FactionRules();
	FactionRules(std::istream& theStream);

	void updateFactionRules(const std::set<std::string>& majorIdeologies);
	void generateRuleGroups(const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getImportedRules() const { return importedRules; }
	[[nodiscard]] const auto& getIdeologicalRules() const { return ideologicalRules; }
	[[nodiscard]] const auto& getIdeologicalRuleGroups() const { return factionRuleGroups->getRuleGroups(); }

  private:
	std::map<std::string, std::vector<std::shared_ptr<FactionRule>>> importedRules;
	std::vector<FactionRule> ideologicalRules;
	std::unique_ptr<FactionRuleGroups> factionRuleGroups;
};


} // namespace HoI4



#endif // FACTION_RULES_H