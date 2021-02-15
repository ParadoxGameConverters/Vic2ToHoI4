#include "PartyMappingFactory.h"



Mappers::PartyMappingFactory::PartyMappingFactory()
{
	registerKeyword("ruling_ideology", [this](std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		partyMapping->rulingIdeology = ideologyString.getString();
	});
	registerKeyword("vic2_ideology", [this](std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		partyMapping->vic2Ideology = ideologyString.getString();
	});
	registerKeyword("supported_ideology", [this](std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		partyMapping->supportedIdeology = ideologyString.getString();
	});
}


std::unique_ptr<Mappers::PartyMapping> Mappers::PartyMappingFactory::importPartyMapping(std::istream& theStream)
{
	partyMapping = std::make_unique<PartyMapping>();
	parseStream(theStream);
	return std::move(partyMapping);
}