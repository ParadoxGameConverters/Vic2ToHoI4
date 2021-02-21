#include "GovernmentMappingFactory.h"



Mappers::GovernmentMappingFactory::GovernmentMappingFactory()
{
	registerKeyword("vic", [this](std::istream& theStream) {
		governmentMapping->vic2Government = commonItems::getString(theStream);
	});
	registerKeyword("tag_required", [this](std::istream& theStream) {
		governmentMapping->tagRequired = commonItems::getString(theStream);
	});
	registerKeyword("ruling_party", [this](std::istream& theStream) {
		governmentMapping->rulingPartyRequired = commonItems::getString(theStream);
	});
	registerKeyword("hoi_gov", [this](std::istream& theStream) {
		governmentMapping->hoI4GovernmentIdeology = commonItems::getString(theStream);
	});
	registerKeyword("hoi_leader", [this](std::istream& theStream) {
		governmentMapping->hoI4LeaderIdeology = commonItems::getString(theStream);
	});
}


std::unique_ptr<Mappers::GovernmentMapping> Mappers::GovernmentMappingFactory::importMapping(std::istream& theStream)
{
	governmentMapping = std::make_unique<GovernmentMapping>();
	parseStream(theStream);
	return std::move(governmentMapping);
}