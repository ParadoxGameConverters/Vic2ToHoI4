#include "src/HOI4World/Factions/FactionRules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Factions/FactionRuleGroups.h"
#include <ranges>



HoI4::FactionRules::FactionRules()
{
	Log(LogLevel::Info) << "\tImporting faction rules";

	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		const FactionRules& ideologyRules(theStream);
		for (const auto& rule: ideologyRules.ideologicalRules)
		{
			importedRules[ideology].push_back(std::make_shared<FactionRule>(rule));
		}
	});
	parseFile(std::filesystem::path("Configurables") / "ideological_faction_rules.txt");
}


HoI4::FactionRules::FactionRules(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& theStream) {
		ideologicalRules.push_back(FactionRule(id, theStream));
	});
	parseStream(theStream);
}


void HoI4::FactionRules::updateFactionRules(const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& hoi4Path)
{
	Log(LogLevel::Info) << "\tUpdating ideological faction rules";

	updateCallToWarRuleFactionLeaderOnly(majorIdeologies);
	updateGuaranteeThreatReduction15(majorIdeologies);
	updateChangeLeaderRuleNever(majorIdeologies);
	updateDismissalRuleWorldTension(majorIdeologies);
	updateJoiningRulesDifferentIdeology(majorIdeologies);
	updateJoiningRuleHasNoOffensiveWar(majorIdeologies);
	updatePeaceRulePuppetingFocus(majorIdeologies);
	updatePeaceRuleLiberationFocus(majorIdeologies);
	updatePeaceRuleConquestFocus(majorIdeologies);

	FactionRuleGroups factionRuleGroups(hoi4Path);
	for (const auto& [ideology, rules]: importedRules)
	{
		for (const auto& rule: rules)
		{
			if (majorIdeologies.contains(ideology))
			{
				ideologicalRules.push_back(*rule);
			}
			else
			{
				factionRuleGroups.removeRule(rule->getId());
				ideologicalRuleGroups = factionRuleGroups.getRuleGroups();
			}
		}
	}
}


std::shared_ptr<HoI4::FactionRule> HoI4::FactionRules::getRule(const std::string& ruleId)
{
	for (auto& rules: importedRules | std::views::values)
	{
		for (auto& rule: rules)
		{
			if (rule->getId() == ruleId)
			{
				return rule;
			}
		}
	}

	return nullptr;
}


void HoI4::FactionRules::updateCallToWarRuleFactionLeaderOnly(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("call_to_war_rule_faction_leader_only"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = { \n";
		aiWillDoStr += "\t\t\tadd = 2\n";
		aiWillDoStr += "\t\t\tis_faction_leader = yes\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\tNOT = { has_government = democratic }\n";
		}
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updateGuaranteeThreatReduction15(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("guarantee_threat_reduction_15"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = { \n";
		aiWillDoStr += "\t\t\tadd = 2\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\thas_government = democratic\n";
		}
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updateChangeLeaderRuleNever(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("change_leader_rule_never"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {  \n";
		aiWillDoStr += "\t\t\tadd = 5\n";
		if (majorIdeologies.contains("fascism"))
		{
			aiWillDoStr += "\t\t\thas_government = fascism\n";
		}
		aiWillDoStr += "\t\t\tis_faction_leader = yes \n";
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updateDismissalRuleWorldTension(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("dismissal_rule_world_tension"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {  \n";
		aiWillDoStr += "\t\t\tadd = 1\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\thas_government = democratic\n";
		}
		aiWillDoStr += "\t\t\tis_faction_leader = yes \n";
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updateJoiningRulesDifferentIdeology(const std::set<std::string>& majorIdeologies)
{
	const std::map<std::string, std::string>& ideologyAdjMap = {{"democratic", "democratic"},
		 {"communism", "communist"},
		 {"fascism", "fasist"},
		 {"radical", "radical"},
		 {"absolutist", "absolutist"},
		 {"neutrality", "unaligned"}};

	const std::vector<std::string>& evilIdeologiesSorted = {"fascism", "communism", "radical", "absolutist"};

	for (const auto& ideology: majorIdeologies)
	{
		const auto& ideologyAdj = ideologyAdjMap.at(ideology);
		if (auto rule = getRule("joining_rule_non_" + ideologyAdj); rule)
		{
			std::string aiWillDoStr = "= {\n";
			aiWillDoStr += "\t\tbase = 0\n";
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 1\n";
			aiWillDoStr += "\t\t\tNOT = { has_government = " + ideology + " }\n";
			aiWillDoStr += "\t\t}\n";
			for (const auto& evilIdeology: evilIdeologiesSorted)
			{
				if (ideology != evilIdeology && majorIdeologies.contains(evilIdeology))
				{
					aiWillDoStr += "\t\tmodifier = {\n";
					aiWillDoStr += "\t\t\tadd = 1\n";
					aiWillDoStr += "\t\t\thas_government = " + evilIdeology + "\n";
					aiWillDoStr += "\t\t}\n";
					break;
				}
			}
			aiWillDoStr += "\t}\n";
			rule->setAiWillDo(aiWillDoStr);
		}
	}
}


void HoI4::FactionRules::updateJoiningRuleHasNoOffensiveWar(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("joining_rule_has_no_offensive_war"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {\n";
		aiWillDoStr += "\t\t\tadd = 2\n";
		aiWillDoStr += "\t\t\tOR = {\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\t\thas_government = democratic\n";
		}
		aiWillDoStr += "\t\t\t\thas_government = neutrality\n";
		aiWillDoStr += "\t\t\t}\n";
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updatePeaceRulePuppetingFocus(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("faction_peace_rule_puppeting_focus"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		if (majorIdeologies.contains("communism"))
		{
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 1\n";
			aiWillDoStr += "\t\t\thas_government = communism\n";
			aiWillDoStr += "\t\t}\n";
		}
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updatePeaceRuleLiberationFocus(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("faction_peace_rule_liberation_focus"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 1\n";
			aiWillDoStr += "\t\t\thas_government = democratic\n";
			aiWillDoStr += "\t\t}\n";
		}
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}


void HoI4::FactionRules::updatePeaceRuleConquestFocus(const std::set<std::string>& majorIdeologies)
{
	if (auto rule = getRule("faction_peace_rule_conquest_focus"); rule)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		if (majorIdeologies.contains("fascism"))
		{
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 2\n";
			aiWillDoStr += "\t\t\thas_government = fascism\n";
			aiWillDoStr += "\t\t}\n";
		}
		aiWillDoStr += "\t}\n";
		rule->setAiWillDo(aiWillDoStr);
	}
}