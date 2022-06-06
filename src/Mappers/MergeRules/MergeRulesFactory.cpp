#include "MergeRulesFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "MergeRule.h"



Mappers::MergeRules::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		const auto theRule = *mergeRuleFactory.importMergeRule(theStream);
		if (theRule.isEnabled())
		{
			mergeRules->rules.insert(std::make_pair(theRule.getMaster(), theRule.getSlaves()));
		}
	});
}


std::unique_ptr<Mappers::MergeRules> Mappers::MergeRules::Factory::importMergeRules()
{
	mergeRules = std::make_unique<MergeRules>();
	parseFile("Configurables/merge_nations.txt");
	return std::move(mergeRules);
}