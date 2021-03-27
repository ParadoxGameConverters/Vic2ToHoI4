#include "IdeologyToPortraitsMappingFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include <algorithm>
#include <random>



Mappers::IdeologyToPortraitsMappingFactory::IdeologyToPortraitsMappingFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		auto strings = commonItems::stringList(theStream).getStrings();
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(strings.begin(), strings.end(), g);
		theMap.insert(make_pair(ideology, strings));
	});
}


std::map<std::string, std::vector<std::string>> Mappers::IdeologyToPortraitsMappingFactory::importMapping(
	 std::istream& theStream)
{
	theMap.clear();
	parseStream(theStream);
	return theMap;
}