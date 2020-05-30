#include "WarGoal.h"
#include "ParserHelpers.h"



Vic2::WarGoal::WarGoal(std::istream& theStream)
{
	registerKeyword("casus_belli", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString cbString(theStream);
		CB = cbString.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}