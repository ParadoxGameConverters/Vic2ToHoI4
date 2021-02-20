#include "IdeologyMappingFactory.h"



Mappers::IdeologyMappingFactory::IdeologyMappingFactory()
{
	registerKeyword("ruling_ideology", [this](std::istream& theStream) {
		ideologyMapping->rulingIdeology = commonItems::singleString(theStream).getString();
	});
	registerKeyword("vic2_ideology", [this](std::istream& theStream) {
		ideologyMapping->vic2Ideology = commonItems::singleString(theStream).getString();
	});
	registerKeyword("supported_ideology", [this](std::istream& theStream) {
		ideologyMapping->supportedIdeology = commonItems::singleString(theStream).getString();
	});
}


std::unique_ptr<Mappers::IdeologyMapping> Mappers::IdeologyMappingFactory::importIdeologyMapping(
	 std::istream& theStream)
{
	ideologyMapping = std::make_unique<IdeologyMapping>();
	parseStream(theStream);
	return std::move(ideologyMapping);
}