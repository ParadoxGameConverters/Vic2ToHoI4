#include "RegionFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Region::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		region->name = commonItems::getString(theStream);
	});
	registerKeyword("adjective", [this](std::istream& theStream) {
		region->adjective = commonItems::getString(theStream);
	});
	registerKeyword("provinces", [this](std::istream& theStream) {
		region->provinces = commonItems::getInts(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}



std::unique_ptr<HoI4::Region> HoI4::Region::Factory::importRegion(std::istream& theStream)
{
	region = std::make_unique<Region>();
	parseStream(theStream);
	return std::move(region);
}