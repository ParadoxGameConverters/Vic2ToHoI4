#include "BuildingReader.h"
#include "ParserHelpers.h"



Vic2::BuildingReader::BuildingReader()
{
	registerKeyword("level", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt levelInt(theStream);
		level = levelInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


int Vic2::BuildingReader::getLevel(std::istream& theStream)
{
	level = 0;
	parseStream(theStream);
	return level;
}
