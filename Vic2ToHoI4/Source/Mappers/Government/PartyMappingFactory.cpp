#include "PartyMappingFactory.h"



Mappers::PartyMappingFactory::PartyMappingFactory()
{
	registerKeyword("ruling_ideology", [this](std::istream& theStream) {
		partyMapping->rulingIdeology = commonItems::singleString(theStream).getString();
	});
	registerKeyword("vic2_ideology", [this](std::istream& theStream) {
		partyMapping->vic2Ideology = commonItems::singleString(theStream).getString();
	});
	registerKeyword("supported_ideology", [this](std::istream& theStream) {
		partyMapping->supportedIdeology = commonItems::singleString(theStream).getString();
	});
}


std::unique_ptr<Mappers::PartyMapping> Mappers::PartyMappingFactory::importPartyMapping(std::istream& theStream)
{
	partyMapping = std::make_unique<PartyMapping>();
	parseStream(theStream);
	return std::move(partyMapping);
}