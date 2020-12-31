#include "RegionsFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Regions::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& region, std::istream& theStream) {
		for (const auto province: commonItems::intList{theStream}.getInts())
		{
			theRegions->regionsMap.insert(std::make_pair(province, region));
		}
	});
}


std::unique_ptr<HoI4::Regions> HoI4::Regions::Factory::getRegions()
{
	theRegions = std::make_unique<Regions>();

	parseFile("./DataFiles/Map/regions.txt");

	return std::move(theRegions);
}