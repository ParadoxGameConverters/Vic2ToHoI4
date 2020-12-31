#include "WarGoalFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::WarGoalFactory::WarGoalFactory()
{
	registerKeyword("casus_belli", [this](const std::string& unused, std::istream& theStream) {
		CB = commonItems::singleString{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::string Vic2::WarGoalFactory::getCB(std::istream& theStream)
{
	CB.clear();
	parseStream(theStream);
	return CB;
}