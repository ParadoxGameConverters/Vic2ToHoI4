#include "IdeologyToPortraitsMappingFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Mappers::IdeologyToPortraitsMappingFactory::IdeologyToPortraitsMappingFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		auto strings = commonItems::stringList(theStream).getStrings();
		theMap.emplace(ideology, strings);
	});
}


std::map<std::string, std::vector<std::string>> Mappers::IdeologyToPortraitsMappingFactory::importMapping(
	 std::istream& theStream)
{
	theMap.clear();
	parseStream(theStream);
	return theMap;
}