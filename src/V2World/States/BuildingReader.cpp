#include "src/V2World/States/BuildingReader.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::BuildingReader::BuildingReader()
{
	registerKeyword("level", [this](std::istream& theStream) {
		level = commonItems::singleInt{theStream}.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


int Vic2::BuildingReader::getLevel(std::istream& theStream)
{
	level = 0;
	parseStream(theStream);
	return level;
}
