#include "src/V2World/Countries/CommonCountriesDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/V2World/Countries/CommonCountryDataFactory.h"
#include <fstream>



namespace
{

std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> ProcessCountriesDotTxt(
	 const std::string& country_list_file,
	 const commonItems::ModFilesystem& mod_filesystem)
{
	std::map<std::string, Vic2::CommonCountryData> common_countries_data;
	std::vector<Vic2::Party> parties;

	if (const std::optional<std::string> possible_file = mod_filesystem.GetActualFileLocation(country_list_file);
		 possible_file)
	{
		Vic2::CommonCountryData::Factory common_country_data_factory;

		commonItems::parser countries_parser;
		countries_parser.registerKeyword("dynamic_tags", commonItems::ignoreItem);
		countries_parser.registerRegex(commonItems::catchallRegex,
			 [&common_countries_data, &parties, &common_country_data_factory, mod_filesystem](const std::string& tag,
				  std::istream& input_stream) {
				 const std::string country_file_name = commonItems::getString(input_stream);
				 const std::unique_ptr<Vic2::CommonCountryData> country_data =
					  common_country_data_factory.ImportCommonCountryData(country_file_name, mod_filesystem);
				 common_countries_data[tag] = *country_data;
				 for (const Vic2::Party& party: country_data->GetParties())
				 {
					 parties.emplace_back(party);
				 }
			 });

		countries_parser.parseFile(*possible_file);
	}

	return std::make_tuple(common_countries_data, parties);
}

} // namespace


std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> Vic2::ImportCommonCountriesData(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	Log(LogLevel::Info) << "\tReading country files";
	return ProcessCountriesDotTxt("/common/countries.txt", mod_filesystem);
}