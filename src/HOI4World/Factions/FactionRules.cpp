#include "src/HOI4World/Factions/FactionRules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
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
			importedRules[ideology].push_back(rule);
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


void HoI4::FactionRules::updateFactionRules(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating ideological faction rules";

	for (auto& [ideology, rules]: importedRules)
	{
		if (majorIdeologies.contains(ideology))
		{
			for (auto& rule: rules)
			{
				rule.updateRule(ideology, majorIdeologies);
				ideologicalRules.push_back(rule);
			}
		}
	}
}


void HoI4::FactionRules::generateRuleGroups(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tGenerating faction rule groups";

	factionRuleGroups = std::make_unique<FactionRuleGroups>(std::filesystem::path("Configurables") / "rule_groups.txt");

	for (const auto& [ideology, rules]: importedRules)
	{
		if (!majorIdeologies.contains(ideology))
		{
			for (const auto& rule: rules)
			{
				factionRuleGroups->removeRule(rule.getId());
			}
		}
	}
}