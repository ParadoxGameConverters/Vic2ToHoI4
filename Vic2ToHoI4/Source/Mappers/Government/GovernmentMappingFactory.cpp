#include "GovernmentMappingFactory.h"



Mappers::GovernmentMappingFactory::GovernmentMappingFactory()
{
	registerKeyword("vic", [this](std::istream& theStream) {
		commonItems::singleString vic2Government(theStream);
		governmentMapping->vic2Government = vic2Government.getString();
	});
	registerKeyword("tag_required", [this](std::istream& theStream) {
		governmentMapping->tagRequired = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("ruling_party", [this](std::istream& theStream) {
		commonItems::singleString rulingParty(theStream);
		governmentMapping->rulingPartyRequired = rulingParty.getString();
	});
	registerKeyword("hoi_gov", [this](std::istream& theStream) {
		commonItems::singleString hoi4Government(theStream);
		governmentMapping->HoI4GovernmentIdeology = hoi4Government.getString();
	});
	registerKeyword("hoi_leader", [this](std::istream& theStream) {
		commonItems::singleString hoi4Leader(theStream);
		governmentMapping->HoI4LeaderIdeology = hoi4Leader.getString();
	});
}


std::unique_ptr<Mappers::GovernmentMapping> Mappers::GovernmentMappingFactory::importMapping(std::istream& theStream)
{
	governmentMapping = std::make_unique<GovernmentMapping>();
	parseStream(theStream);
	return std::move(governmentMapping);
}