#include "src/V2World/Countries/CommonCountriesDataFactory.h"
#include "external/common_items/Log.h"
#include "src/V2World/Countries/CommonCountryDataFactory.h"
#include <fstream>



namespace
{

bool ShouldLineBeSkipped(std::string line)
{
	line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
	return line.starts_with('#') || line.size() < 3 || line.starts_with("dynamic_tags");
}


std::string ExtractCountryFileName(const std::string& country_file_line)
{
	const auto start = country_file_line.find_first_of('/');
	const auto size = country_file_line.find_last_of('\"') - start;

	return country_file_line.substr(start, size);
}


std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> ProcessCountriesDotTxt(
	 const std::string& country_list_file,
	 const commonItems::ModFilesystem& mod_filesystem)
{
	std::map<std::string, Vic2::CommonCountryData> common_countries_data;
	std::vector<Vic2::Party> parties;

	const auto possible_file = mod_filesystem.GetActualFileLocation(country_list_file);
	if (!possible_file)
	{
		return std::make_tuple(common_countries_data, parties);
	}

	std::ifstream vic2_countries_input(*possible_file);
	if (!vic2_countries_input.is_open())
	{
		return std::make_tuple(common_countries_data, parties);
	}

	Vic2::CommonCountryData::Factory common_country_data_factory;
	while (!vic2_countries_input.eof())
	{
		std::string line;
		getline(vic2_countries_input, line);
		if (ShouldLineBeSkipped(line))
		{
			continue;
		}

		auto tag = line.substr(0, 3);
		auto country_file_name = ExtractCountryFileName(line);
		auto country_data = common_country_data_factory.ImportCommonCountryData(country_file_name, mod_filesystem);
		common_countries_data[tag] = *country_data;
		for (const auto& party: country_data->GetParties())
		{
			parties.emplace_back(party);
		}
	}

	vic2_countries_input.close();

	return std::make_tuple(common_countries_data, parties);
}

} // namespace


std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> Vic2::ImportCommonCountriesData(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	Log(LogLevel::Info) << "\tReading country files";
	return ProcessCountriesDotTxt("/common/countries.txt", mod_filesystem);
}