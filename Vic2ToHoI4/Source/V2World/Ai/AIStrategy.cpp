#include "AIStrategy.h"
#include "ParserHelpers.h"



Vic2::AIStrategy::AIStrategy(const std::string& strategyType, std::istream& theStream): type(strategyType)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString stateString(theStream);
		id = stateString.getString();
	});
	registerKeyword("value", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt valueInt(theStream);
		value = valueInt.getInt();
	});
	registerRegex("[A-Za-z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}