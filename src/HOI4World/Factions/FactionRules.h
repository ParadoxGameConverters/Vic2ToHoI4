#ifndef FACTION_RULES_H
#define FACTION_RULES_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/Factions/FactionRule.h"



namespace HoI4
{

class FactionRules: commonItems::parser
{
  public:
	FactionRules();
	FactionRules(std::istream& theStream);

	void updateFactionRules(const std::set<std::string>& majorIdeologies, const std::filesystem::path& hoi4Path);

	void updateCallToWarRuleFactionLeaderOnly(const std::set<std::string>& majorIdeologies);
	void updateGuaranteeThreatReduction15(const std::set<std::string>& majorIdeologies);
	void updateChangeLeaderRuleNever(const std::set<std::string>& majorIdeologies);
	void updateDismissalRuleWorldTension(const std::set<std::string>& majorIdeologies);
	void updateJoiningRulesDifferentIdeology(const std::set<std::string>& majorIdeologies);
	void updateJoiningRuleHasNoOffensiveWar(const std::set<std::string>& majorIdeologies);
	void updatePeaceRulePuppetingFocus(const std::set<std::string>& majorIdeologies);
	void updatePeaceRuleLiberationFocus(const std::set<std::string>& majorIdeologies);
	void updatePeaceRuleConquestFocus(const std::set<std::string>& majorIdeologies);

	std::shared_ptr<HoI4::FactionRule> getRule(const std::string& ruleId);

	[[nodiscard]] const auto& getImportedRules() const { return importedRules; }
	[[nodiscard]] const auto& getIdeologicalRules() const { return ideologicalRules; }
	[[nodiscard]] const auto& getIdeologicalRuleGroups() const { return ideologicalRuleGroups; }

  private:
	std::map<std::string, std::vector<std::shared_ptr<FactionRule>>> importedRules;
	std::vector<FactionRule> ideologicalRules;
	std::map<std::string, std::vector<std::string>> ideologicalRuleGroups;
};


} // namespace HoI4



#endif // FACTION_RULES_H