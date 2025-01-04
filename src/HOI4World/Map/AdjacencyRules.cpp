#include "src/HOI4World/Map/AdjacencyRules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Map/AdjacencyRule.h"
#include <ranges>



HoI4::AdjacencyRules::AdjacencyRules(const std::map<int, State>& states)
{
	Log(LogLevel::Info) << "\tImporting adjacency rules";

	importDefaultAdjacencyRules();
	updateRules(states);
}

void HoI4::AdjacencyRules::importDefaultAdjacencyRules()
{
	registerKeywords();
	parseFile("Configurables/Map/adjacency_rules.txt");
	clearRegisteredKeywords();
}

void HoI4::AdjacencyRules::registerKeywords()
{
	registerKeyword("adjacency_rule", [this](std::istream& theStream) {
		const AdjacencyRule newRule(theStream);
		rules.emplace(std::make_pair(newRule.getName(), newRule));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

void HoI4::AdjacencyRules::updateRules(const std::map<int, State>& states)
{
	for (auto rule: rules | std::views::values)
	{
		rule.updateIsDisabledStr(states);
	}
}