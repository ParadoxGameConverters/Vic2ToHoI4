#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"

HoI4::ScenarioBuilder::ConfigParser::ConfigParser(std::string filename)
{
	registerKeys();
	parseFile(filename);
	clearRegisteredKeywords();
}

void HoI4::ScenarioBuilder::ConfigParser::registerKeys()
{
	registerKeyword("valid", [this](std::istream& theStream) {
		possibleRoles = commonItems::getStrings(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
