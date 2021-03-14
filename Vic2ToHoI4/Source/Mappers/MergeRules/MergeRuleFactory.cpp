#include "MergeRuleFactory.h"
#include "ParserHelpers.h"



Mappers::MergeRule::Factory::Factory()
{
	registerKeyword("merge", [this](std::istream& theStream) {
		commonItems::singleString enabledString(theStream);
		mergeRule->enabled = (enabledString.getString() == "yes");
	});
	registerKeyword("master", [this](std::istream& theStream) {
		commonItems::singleString masterString(theStream);
		mergeRule->master = masterString.getString();
	});
	registerKeyword("slave", [this](std::istream& theStream) {
		commonItems::singleString slaveString(theStream);
		mergeRule->slaves.push_back(slaveString.getString());
	});
}


std::unique_ptr<Mappers::MergeRule> Mappers::MergeRule::Factory::importMergeRule(std::istream& theStream)
{
	mergeRule = std::make_unique<MergeRule>();
	parseStream(theStream);
	return std::move(mergeRule);
}