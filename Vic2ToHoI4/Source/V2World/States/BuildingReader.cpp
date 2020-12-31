#include "BuildingReader.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::BuildingReader::BuildingReader()
{
	registerKeyword("level", [this](const std::string& unused, std::istream& theStream) {
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
