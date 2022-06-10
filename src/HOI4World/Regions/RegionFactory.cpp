#include "src/HOI4World/Regions/RegionFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::Region::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		region->name = commonItems::getString(theStream);
	});
	registerKeyword("adjective", [this](std::istream& theStream) {
		region->adjective = commonItems::getString(theStream);
	});
	registerKeyword("level", [this](std::istream& theStream) {
		region->level = commonItems::getString(theStream);
	});
	registerKeyword("subregions", [this](std::istream& theStream) {
		region->subregions = commonItems::getStrings(theStream);
	});
	registerKeyword("blocked", [this](std::istream& theStream) {
		region->blocked = commonItems::getStrings(theStream);
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