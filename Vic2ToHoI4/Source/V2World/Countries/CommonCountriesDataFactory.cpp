#include "CommonCountriesDataFactory.h"
#include "CommonCountryDataFactory.h"
#include "Log.h"
#include <fstream>



bool shouldLineBeSkipped(const std::string& line)
{
	return (line[0] == '#') || (line.size() < 3) || (line.substr(0, 12) == "dynamic_tags");
}


std::string extractCountryFileName(const std::string& countryFileLine)
{
	const auto start = countryFileLine.find_first_of('/');
	const auto size = countryFileLine.find_last_of('\"') - start;

	return countryFileLine.substr(start, size);
}


std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> processCountriesDotTxt(
	 const std::string& countryListFile,
	 const std::optional<std::string>& modFolder,
	 const Configuration& theConfiguration)
{
	std::map<std::string, Vic2::CommonCountryData> commonCountriesData;
	std::vector<Vic2::Party> parties;

	std::ifstream V2CountriesInput(countryListFile);
	if (!V2CountriesInput.is_open())
	{
		return std::make_tuple(commonCountriesData, parties);
	}

	Vic2::CommonCountryData::Factory commonCountryDataFactory;

	while (!V2CountriesInput.eof())
	{
		std::string line;
		getline(V2CountriesInput, line);
		if (shouldLineBeSkipped(line))
		{
			continue;
		}

		auto tag = line.substr(0, 3);
		auto countryFileName = extractCountryFileName(line);
		auto countryData = commonCountryDataFactory.importCommonCountryData(countryFileName, modFolder, theConfiguration);
		commonCountriesData[tag] = *countryData;
		for (const auto& party: countryData->getParties())
		{
			parties.emplace_back(party);
		}
	}

	V2CountriesInput.close();

	return std::make_tuple(commonCountriesData, parties);
}


std::tuple<std::map<std::string, Vic2::CommonCountryData>, std::vector<Vic2::Party>> Vic2::importCommonCountriesData(
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tReading country files";

	for (const auto& vic2Mod: theConfiguration.getVic2Mods())
	{
		std::string modFolder = theConfiguration.getVic2ModPath() + "/" + vic2Mod.getDirectory();
		auto [commonCountriesData, parties] =
			 processCountriesDotTxt(modFolder + "/common/countries.txt", modFolder, theConfiguration);
		if (!commonCountriesData.empty())
		{
			return std::make_tuple(commonCountriesData, parties);
		}
	}

	return processCountriesDotTxt(theConfiguration.getVic2Path() + "/common/countries.txt",
		 std::nullopt,
		 theConfiguration);
}