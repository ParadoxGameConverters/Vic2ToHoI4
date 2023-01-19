#include "src/V2World/EU4ToVic2Data/CountryDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::CountryData::Factory::Factory()
{
	registerKeyword("last_dynasty", [this](std::istream& theStream) {
		countryData->lastDynasty = commonItems::singleString(theStream).getString();
	});
	registerKeyword("last_ruler_name", [this](std::istream& theStream) {
		countryData->lastMonarch = commonItems::singleString(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::CountryData> Vic2::CountryData::Factory::importCountryData(std::istream& theStream)
{
	countryData = std::make_unique<CountryData>();
	parseStream(theStream);
	return std::move(countryData);
}