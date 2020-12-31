#include "CountryNameMappingFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



mappers::CountryNameMappingFactory::CountryNameMappingFactory()
{
	registerKeyword("vic2_gov", [this](const std::string& unused, std::istream& theStream) {
		countryNameMapping->vic2Government = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("vic2_tag", [this](const std::string& unused, std::istream& theStream) {
		countryNameMapping->vic2Tag = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("hoi4_ideology", [this](const std::string& unused, std::istream& theStream) {
		countryNameMapping->hoi4Ideology = commonItems::singleString{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<mappers::CountryNameMapping> mappers::CountryNameMappingFactory::importMapping(std::istream& theStream)
{
	countryNameMapping = std::make_unique<CountryNameMapping>();
	parseStream(theStream);
	return std::move(countryNameMapping);
}