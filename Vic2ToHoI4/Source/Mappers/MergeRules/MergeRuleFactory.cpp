#include "MergeRuleFactory.h"
#include "ParserHelpers.h"



Mappers::MergeRule::Factory::Factory()
{
	registerKeyword("merge", [this](std::istream& theStream) {
		mergeRule->enabled = commonItems::singleString(theStream).getString() == "yes";
	});
	registerKeyword("master", [this](std::istream& theStream) {
		mergeRule->master = commonItems::singleString(theStream).getString();
	});
	registerKeyword("slave", [this](std::istream& theStream) {
		mergeRule->slaves.push_back(commonItems::singleString(theStream).getString());
	});
}


std::unique_ptr<Mappers::MergeRule> Mappers::MergeRule::Factory::importMergeRule(std::istream& theStream)
{
	mergeRule = std::make_unique<MergeRule>();
	parseStream(theStream);
	return std::move(mergeRule);
}