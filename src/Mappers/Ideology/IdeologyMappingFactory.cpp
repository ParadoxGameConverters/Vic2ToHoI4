#include "IdeologyMappingFactory.h"
#include "ParserHelpers.h"



Mappers::IdeologyMappingFactory::IdeologyMappingFactory()
{
	registerKeyword("ruling_ideology", [this](std::istream& theStream) {
		ideologyMapping->rulingIdeology = commonItems::getString(theStream);
	});
	registerKeyword("vic2_ideology", [this](std::istream& theStream) {
		ideologyMapping->vic2Ideology = commonItems::getString(theStream);
	});
	registerKeyword("supported_ideology", [this](std::istream& theStream) {
		ideologyMapping->supportedIdeology = commonItems::getString(theStream);
	});
}


std::unique_ptr<Mappers::IdeologyMapping> Mappers::IdeologyMappingFactory::importIdeologyMapping(
	 std::istream& theStream)
{
	ideologyMapping = std::make_unique<IdeologyMapping>();
	parseStream(theStream);
	return std::move(ideologyMapping);
}