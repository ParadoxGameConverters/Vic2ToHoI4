#include "src/V2World/Localisations/LocalisationsFactory.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>



std::unique_ptr<Vic2::Localisations> Vic2::Localisations::Factory::ImportLocalisations(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	Log(LogLevel::Info) << "Reading Vic2 localisation";

	for (const auto& file: mod_filesystem.GetAllFilesInFolder("localisation"))
	{
		ReadFromFile(file);
	}
	for (const auto& file_name: commonItems::GetAllFilesInFolder("Configurables/Vic2Localisations"))
	{
		ReadFromFile("Configurables/Vic2Localisations/" + file_name);
	}

	return std::make_unique<Localisations>(localisations_, localisation_to_key_map_);
}


void Vic2::Localisations::Factory::ReadFromFile(const std::string& fileName)
{
	std::ifstream in(fileName);

	while (!in.eof())
	{
		std::string line;
		getline(in, line);
		if (line[0] != '#')
		{
			ProcessLine(line);
		}
	}

	in.close();
}


constexpr std::array<std::pair<const char*, Vic2::Encoding>, 13> languages = {{
	 {"english", Vic2::Encoding::Win1252},
	 {"french", Vic2::Encoding::Win1252},
	 {"german", Vic2::Encoding::Win1252},
	 {"polish", Vic2::Encoding::Win1250},
	 {"spanish", Vic2::Encoding::Win1252},
	 {"italian", Vic2::Encoding::Win1252},
	 {"swedish", Vic2::Encoding::Win1250},
	 {"czech", Vic2::Encoding::Win1250},
	 {"hungarian", Vic2::Encoding::Win1250},
	 {"dutch", Vic2::Encoding::Win1252},
	 {"braz_por", Vic2::Encoding::Win1252},
	 {"russian", Vic2::Encoding::Win1251},
	 {"finnish", Vic2::Encoding::Win1252},
}};
void Vic2::Localisations::Factory::ProcessLine(const std::string& line)
{
	auto division = line.find_first_of(';');
	const auto key = line.substr(0, division);

	for (const auto& [language, encoding]: languages)
	{
		auto [rawLocalisation, newDivision] = ExtractNextLocalisation(line, division);
		division = newDivision;

		auto UTF8Result = ConvertToUtf8(rawLocalisation, encoding);

		if (strcmp(language, "english") == 0)
		{
			localisation_to_key_map_[UTF8Result] = key;
		}

		if (!UTF8Result.empty())
		{
			localisations_[key][language] = UTF8Result;
		}
		else if (strcmp(language, "english") != 0)
		{
			localisations_[key][language] = localisations_[key]["english"];
		}
	}
}


std::tuple<std::string, size_t> Vic2::Localisations::Factory::ExtractNextLocalisation(const std::string& line,
	 size_t division)
{
	const auto frontDivision = division + 1;
	division = line.find_first_of(';', frontDivision);
	return {line.substr(frontDivision, division - frontDivision), division};
}


std::string Vic2::Localisations::Factory::ConvertToUtf8(const std::string& rawLocalisation, Encoding encoding)
{
	if (encoding == Encoding::Win1250)
	{
		return commonItems::convertWin1250ToUTF8(rawLocalisation);
	}
	if (encoding == Encoding::Win1251)
	{
		return commonItems::convertWin1251ToUTF8(rawLocalisation);
	}

	// if (encoding == Encoding::Win1252)
	return commonItems::convertWin1252ToUTF8(rawLocalisation);
}