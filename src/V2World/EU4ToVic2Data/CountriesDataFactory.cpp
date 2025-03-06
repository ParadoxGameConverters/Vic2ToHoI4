#include "src/V2World/EU4ToVic2Data/CountriesDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/OSCompatibilityLayer.h"



Vic2::CountriesData::Factory::Factory()
{
	parser_.registerRegex(commonItems::catchallRegex, [this](const std::string& tag, std::istream& theStream) {
		countries_data_->countriesData.emplace(tag, *country_data_factory_.importCountryData(theStream));
	});
}


std::unique_ptr<Vic2::CountriesData> Vic2::CountriesData::Factory::ImportCountriesData(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	countries_data_ = std::make_unique<CountriesData>();

	if (const auto possible_file = mod_filesystem.GetActualFileLocation("common/botanical_expedition.txt");
		 possible_file)
	{
		parser_.parseFile(*possible_file);
	}
	return std::move(countries_data_);
}