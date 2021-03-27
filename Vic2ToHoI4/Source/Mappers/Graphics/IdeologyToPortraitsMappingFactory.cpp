#include "IdeologyToPortraitsMappingFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Mappers::IdeologyToPortraitsMappingFactory::IdeologyToPortraitsMappingFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		auto strings = commonItems::stringList(theStream).getStrings();
	});
}


std::map<std::string, std::vector<std::string>> Mappers::IdeologyToPortraitsMappingFactory::importMapping(
	 std::istream& theStream)
{
	theMap.clear();
	parseStream(theStream);
	return theMap;
}