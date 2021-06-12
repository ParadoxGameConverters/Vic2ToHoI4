#include "CommonRegexes.h"
#include "FactionNameMappingFactory.h"
#include "ParserHelpers.h"



Mappers::FactionNameMappingFactory::FactionNameMappingFactory()
{
	registerKeyword("faction", [this](std::istream& theStream) {
		factionNameMapping->factionName = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("culture", [this](std::istream& theStream) {
		factionNameMapping->hoi4Culture = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("ideology", [this](std::istream& theStream) {
		factionNameMapping->hoi4Ideology = commonItems::singleString{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::FactionNameMapping> Mappers::FactionNameMappingFactory::importMapping(std::istream& theStream)
{
	factionNameMapping = std::make_unique<FactionNameMapping>();
	parseStream(theStream);
	return std::move(factionNameMapping);
}