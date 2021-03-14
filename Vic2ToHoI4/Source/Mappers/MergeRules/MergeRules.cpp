#include "MergeRules.h"
#include "CommonRegexes.h"
#include "MergeRule.h"



MergeRules::MergeRules() noexcept
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ruleName, std::istream& theStream) {
		Mappers::MergeRule theRule(theStream);
		if (theRule.isEnabled())
		{
			rules.insert(std::make_pair(theRule.getMaster(), theRule.getSlaves()));
		}
	});

	parseFile("Configurables/merge_nations.txt");
}