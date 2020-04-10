#include "Vic2Localisations.h"
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



Vic2::Localisations::Localisations() noexcept: localisations(), localisationToKeyMap()
{
	LOG(LogLevel::Info) << "Reading localisation";

	ReadFromAllFilesInFolder(theConfiguration.getVic2Path() + "/localisation");

	for (auto mod: theConfiguration.getVic2Mods())
	{
		LOG(LogLevel::Debug) << "Reading mod localisation";
		ReadFromAllFilesInFolder(theConfiguration.getVic2Path() + "/mod/" + mod + "/localisation");
	}

	if (Utils::DoesFileExist("DataFiles/Vic2Localisations.csv"))
	{
		ReadFromFile("DataFiles/Vic2Localisations.csv");
	}
}


void Vic2::Localisations::ReadFromAllFilesInFolder(const string& folderPath)
{
	set<string> fileNames;
	Utils::GetAllFilesInFolder(folderPath, fileNames);

	for (const auto& fileName: fileNames)
	{
		ReadFromFile(folderPath + '/' + fileName);
	}
}


void Vic2::Localisations::ReadFromFile(const string& fileName)
{
	ifstream in(fileName);

	while (!in.eof())
	{
		string line;
		getline(in, line);
		if (line[0] != '#')
		{
			processLine(line);
		}
	}

	in.close();
}


const string languages[] = {"english",
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
void Vic2::Localisations::processLine(const std::string& line)
{
	int division = line.find_first_of(';');
	string key = line.substr(0, division);

	for (auto language: languages)
	{
		string result = getNextLocalisation(line, division);
		std::string UTF8Result;

		if (language == "english" || language == "french" || language == "german" || language == "spanish" ||
			 language == "italian" || language == "dutch" || language == "braz_por" || language == "finnish")
		{
			UTF8Result = Utils::convertWin1252ToUTF8(result);
		}
		if (language == "polish" || language == "swedish" || language == "czech" ||
			 language == "hungarian") // Swedish = Hungarian again
		{
			UTF8Result = Utils::convertWin1250ToUTF8(result);
		}
		if (language == "russian")
		{
			UTF8Result = Utils::convertWin1251ToUTF8(result);
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


string Vic2::Localisations::getNextLocalisation(const std::string& line, int& division)
{
	int frontDivision = division + 1;
	division = line.find_first_of(';', frontDivision);
	return line.substr(frontDivision, division - frontDivision);
}


void Vic2::Localisations::updateDomainCountry(const string& tag, const string& domainName)
{
	LanguageToLocalisationMap regionLocalisations;
	const auto domainKey = localisationToKeyMap.find(domainName);
	if (domainKey != localisationToKeyMap.end())
	{
		const auto domainLocalisations = localisations.find(domainKey->second);
		if (domainLocalisations != localisations.end())
		{
			for (auto regionInLanguage: domainLocalisations->second)
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

	for (auto nameInLanguage: nameInAllLanguages)
	{
		string replacementName = domainName;
		auto replacementLocalisation = regionLocalisations.find(nameInLanguage.first);
		if (replacementLocalisation != regionLocalisations.end())
		{
			replacementName = replacementLocalisation->second;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not find regions localisation for " << domainName << " in "
										  << nameInLanguage.first;
		}
		string updatedName = nameInLanguage.second;
		size_t regionPos = updatedName.find("$REGION$");
		if (regionPos != string::npos)
		{
			updatedName.replace(regionPos, 8, replacementName);
			KeyToLocalisationsMappings->second[nameInLanguage.first] = updatedName;
		}
	}
}


const optional<string> Vic2::Localisations::getTextInLanguage(const string& key, const string& language) const
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


const map<string, string> Vic2::Localisations::getTextInEachLanguage(const string& key) const
{
	static const map<string, string> noLocalisations;

	const auto KeyToLocalisationsMappings = localisations.find(key);
	if (KeyToLocalisationsMappings == localisations.end())
	{
		return noLocalisations;
	}
	else
	{
		return KeyToLocalisationsMappings->second;
	}
}
