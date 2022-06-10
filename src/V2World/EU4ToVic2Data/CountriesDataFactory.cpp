#include "src/V2World/EU4ToVic2Data/CountriesDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/OSCompatibilityLayer.h"



Vic2::CountriesData::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& tag, std::istream& theStream) {
		countriesData->countriesData.emplace(tag, *countryDataFactory.importCountryData(theStream));
	});
}


std::unique_ptr<Vic2::CountriesData> Vic2::CountriesData::Factory::importCountriesData(
	 const Configuration& configuration)
{
	countriesData = std::make_unique<CountriesData>();

	for (const auto& mod: configuration.getVic2Mods())
	{
		const auto filename = mod.path + "/common/botanical_expedition.txt";
		if (!commonItems::DoesFileExist(filename))
		{
			continue;
		}

		parseFile(filename);
	}

	return std::move(countriesData);
}