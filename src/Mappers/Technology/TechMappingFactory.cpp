#include "TechMappingFactory.h"
#include "external/common_items/ParserHelpers.h"



Mappers::TechMapping::Factory::Factory()
{
	registerKeyword("vic2", [this](std::istream& theStream) {
		techMapping->vic2Requirements.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("limit", [this](std::istream& theStream) {
		techMapping->limit = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("hoi4", [this](std::istream& theStream) {
		techMapping->techs.insert(commonItems::singleString{theStream}.getString());
	});
}


std::unique_ptr<Mappers::TechMapping> Mappers::TechMapping::Factory::importTechMapping(std::istream& theStream)
{
	techMapping = std::make_unique<TechMapping>();
	parseStream(theStream);
	return std::move(techMapping);
}