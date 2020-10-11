#include "LocalisationsFactory.h"
#include "Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <array>
#include <fstream>



std::unique_ptr<Vic2::Localisations> Vic2::Localisations::Factory::importLocalisations(
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "Reading Vic2 localisation";

	ReadFromAllFilesInFolder(theConfiguration.getVic2Path() + "/localisation");

	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		Log(LogLevel::Info) << "\tReading mod localisation";
		ReadFromAllFilesInFolder(theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/localisation");
	}

	if (commonItems::DoesFileExist("DataFiles/Vic2Localisations.csv"))
	{
		ReadFromFile("DataFiles/Vic2Localisations.csv");
	}

	return std::make_unique<Localisations>(localisations, localisationToKeyMap);
}


void Vic2::Localisations::Factory::ReadFromAllFilesInFolder(const std::string& folderPath)
{
	for (const auto& fileName: commonItems::GetAllFilesInFolder(folderPath))
	{
		ReadFromFile(folderPath + '/' + fileName);
	}
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
			processLine(line);
		}
	}

	in.close();
}


const std::array<std::string, 13> languages = {"english",
	 "french",
	 "german",
	 "polish",
	 "spanish",
	 "italian",
	 "swedish",
	 "czech",
	 "hungarian",
	 "dutch",
	 "braz_por",
	 "russian",
	 "finnish"};
void Vic2::Localisations::Factory::processLine(const std::string& line)
{
	auto division = line.find_first_of(';');
	const auto key = line.substr(0, division);

	for (const auto& language: languages)
	{
		auto [rawLocalisation, newDivision] = extractNextLocalisation(line, division);
		division = newDivision;

		auto UTF8Result = convertToUtf8(rawLocalisation, language);

		if (language == "english")
		{
			localisationToKeyMap[UTF8Result] = key;
		}

		if (!UTF8Result.empty())
		{
			localisations[key][language] = UTF8Result;
		}
		else if (language != "english")
		{
			localisations[key][language] = localisations[key]["english"];
		}
	}
}


std::tuple<std::string, size_t> Vic2::Localisations::Factory::extractNextLocalisation(const std::string& line,
	 size_t division)
{
	const auto frontDivision = division + 1;
	division = line.find_first_of(';', frontDivision);
	return {line.substr(frontDivision, division - frontDivision), division};
}


std::string Vic2::Localisations::Factory::convertToUtf8(const std::string& rawLocalisation, const std::string& language)
{
	if (language == "english" || language == "french" || language == "german" || language == "spanish" ||
		 language == "italian" || language == "dutch" || language == "braz_por" || language == "finnish")
	{
		return commonItems::convertWin1252ToUTF8(rawLocalisation);
	}
	else if (language == "polish" || language == "swedish" || language == "czech" ||
				language == "hungarian") // Swedish = Hungarian again
	{
		return commonItems::convertWin1250ToUTF8(rawLocalisation);
	}
	else // if (language == "russian")
	{
		return commonItems::convertWin1251ToUTF8(rawLocalisation);
	}
}