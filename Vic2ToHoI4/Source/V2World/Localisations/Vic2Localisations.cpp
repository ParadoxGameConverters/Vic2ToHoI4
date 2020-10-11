#include "Vic2Localisations.h"
#include "Log.h"



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
