#include "Building.h"
#include "ParserHelpers.h"



Vic2::Building::Building(std::istream& theStream)
{
	registerKeyword("level", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt levelInt(theStream);
		level = levelInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}