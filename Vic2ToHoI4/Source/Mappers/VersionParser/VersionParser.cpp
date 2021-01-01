#include "VersionParser.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



mappers::VersionParser::VersionParser()
{
	registerKeys();
	parseFile("../version.txt");
	clearRegisteredKeywords();
}


mappers::VersionParser::VersionParser(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}


void mappers::VersionParser::registerKeys()
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameStr(theStream);
		name = nameStr.getString();
	});
	registerKeyword("version", [this](std::istream& theStream) {
		const commonItems::singleString versionStr(theStream);
		version = versionStr.getString();
	});
	registerKeyword("descriptionLine", [this](std::istream& theStream) {
		const commonItems::singleString descriptionLineStr(theStream);
		descriptionLine = descriptionLineStr.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}