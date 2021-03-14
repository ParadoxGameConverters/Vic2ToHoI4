#include "MergeRule.h"
#include "ParserHelpers.h"



Mappers::MergeRule::MergeRule(std::istream& theStream)
{
	registerKeyword("merge", [this](std::istream& theStream) {
		commonItems::singleString enabledString(theStream);
		enabled = (enabledString.getString() == "yes");
	});
	registerKeyword("master", [this](std::istream& theStream) {
		commonItems::singleString masterString(theStream);
		master = masterString.getString();
	});
	registerKeyword("slave", [this](std::istream& theStream) {
		commonItems::singleString slaveString(theStream);
		slaves.push_back(slaveString.getString());
	});

	parseStream(theStream);
}