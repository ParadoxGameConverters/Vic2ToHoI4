#include "Vic2Localisations.h"
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



std::string getNextLocalisation(const std::string& line, size_t& division);


std::unique_ptr<Vic2::Localisations> Vic2::Localisations::Parser::importLocalisations(
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


void Vic2::Localisations::Parser::ReadFromAllFilesInFolder(const std::string& folderPath)
{
	for (const auto& fileName: commonItems::GetAllFilesInFolder(folderPath))
	{
		ReadFromFile(folderPath + '/' + fileName);
	}
}


void Vic2::Localisations::Parser::ReadFromFile(const std::string& fileName)
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


const std::string languages[] = {"english",
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
void Vic2::Localisations::Parser::processLine(const std::string& line)
{
	auto division = line.find_first_of(';');
	const auto key = line.substr(0, division);

	for (const auto& language: languages)
	{
		auto result = getNextLocalisation(line, division);
		std::string UTF8Result;

		if (language == "english" || language == "french" || language == "german" || language == "spanish" ||
			 language == "italian" || language == "dutch" || language == "braz_por" || language == "finnish")
		{
			UTF8Result = commonItems::convertWin1252ToUTF8(result);
		}
		if (language == "polish" || language == "swedish" || language == "czech" ||
			 language == "hungarian") // Swedish = Hungarian again
		{
			UTF8Result = commonItems::convertWin1250ToUTF8(result);
		}
		if (language == "russian")
		{
			UTF8Result = commonItems::convertWin1251ToUTF8(result);
		}

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


std::string getNextLocalisation(const std::string& line, size_t& division)
{
	const auto frontDivision = division + 1;
	division = line.find_first_of(';', frontDivision);
	return line.substr(frontDivision, division - frontDivision);
}


void Vic2::Localisations::updateDomainCountry(const std::string& tag, const std::string& domainName)
{
	LanguageToLocalisationMap regionLocalisations;
	const auto domainKey = localisationToKeyMap.find(domainName);
	if (domainKey != localisationToKeyMap.end())
	{
		const auto domainLocalisations = localisations.find(domainKey->second);
		if (domainLocalisations != localisations.end())
		{
			for (const auto& regionInLanguage: domainLocalisations->second)
			{
				regionLocalisations.insert(regionInLanguage);
			}
		}
	}

	const auto KeyToLocalisationsMappings = localisations.find(tag);
	if (KeyToLocalisationsMappings == localisations.end())
	{
		return;
	}
	auto nameInAllLanguages = KeyToLocalisationsMappings->second;

	for (const auto& nameInLanguage: nameInAllLanguages)
	{
		auto replacementName = domainName;
		auto replacementLocalisation = regionLocalisations.find(nameInLanguage.first);
		if (replacementLocalisation != regionLocalisations.end())
		{
			replacementName = replacementLocalisation->second;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find regions localisation for " << domainName << " in "
										  << nameInLanguage.first;
		}
		auto updatedName = nameInLanguage.second;
		const auto regionPos = updatedName.find("$REGION$");
		if (regionPos != std::string::npos)
		{
			updatedName.replace(regionPos, 8, replacementName);
			KeyToLocalisationsMappings->second[nameInLanguage.first] = updatedName;
		}
	}
}


std::optional<std::string> Vic2::Localisations::getTextInLanguage(const std::string& key,
	 const std::string& language) const
{
	const auto KeyToLocalisationsMapping = localisations.find(key);
	if (KeyToLocalisationsMapping == localisations.end())
	{
		return {};
	}

	const auto LanguageToLocalisationMapping = KeyToLocalisationsMapping->second.find(language);
	if (LanguageToLocalisationMapping == KeyToLocalisationsMapping->second.end())
	{
		return {};
	}

	return LanguageToLocalisationMapping->second;
}


std::map<std::string, std::string> Vic2::Localisations::getTextInEachLanguage(const std::string& key) const
{
	if (const auto KeyToLocalisationsMappings = localisations.find(key);
		 KeyToLocalisationsMappings != localisations.end())
	{
		return KeyToLocalisationsMappings->second;
	}
	else
	{
		return std::map<std::string, std::string>{};
	}
}
