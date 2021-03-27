#include "IdeologyToPortraitsMapping.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Mappers::IdeologyToPortraitsMapping::IdeologyToPortraitsMapping(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		commonItems::stringList portraits(theStream);
		theMap.insert(make_pair(ideology, portraits.getStrings()));
	});

	parseStream(theStream);
}