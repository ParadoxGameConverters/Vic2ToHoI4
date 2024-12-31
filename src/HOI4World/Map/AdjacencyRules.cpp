#include "src/HOI4World/Map/AdjacencyRules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Map/AdjacencyRule.h"



HoI4::AdjacencyRules::AdjacencyRules()
{
	Log(LogLevel::Info) << "\tImporting adjacency rules";

	importDefaultAdjacencyRules();
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
		rules[newRule.getName()] = std::make_shared<AdjacencyRule>(newRule);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}