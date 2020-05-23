#include "Names.h"
#include "../../Configuration.h"
#include "CultureNames.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



class cultureGroup: commonItems::parser
{
  public:
	explicit cultureGroup(std::istream& theStream);

	[[nodiscard]] auto getMaleNames() const { return maleNamesMap; }
	[[nodiscard]] auto getSurnames() const { return surnamesMap; }

  private:
	std::map<std::string, std::vector<std::string>> maleNamesMap;
	std::map<std::string, std::vector<std::string>> surnamesMap;
};


cultureGroup::cultureGroup(std::istream& theStream)
{
	registerKeyword("leader", commonItems::ignoreItem);
	registerKeyword("unit", commonItems::ignoreItem);
	registerKeyword("union", commonItems::ignoreItem);
	registerKeyword("is_overseas", commonItems::ignoreItem);
	registerRegex("[A-Za-z0-9\\_]+", [this](const std::string& cultureName, std::istream& theStream) {
		HoI4::culture newCulture(theStream);
		newCulture.convertNamesToUTF8();
		maleNamesMap.insert(make_pair(cultureName, newCulture.takeMaleNames()));
		surnamesMap.insert(make_pair(cultureName, newCulture.takeSurnames()));
	});

	parseStream(theStream);
}


std::unique_ptr<HoI4::Names> HoI4::Names::Factory::getNames(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tParsing names";

	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		Log(LogLevel::Debug) << "Reading mod cultures from " << mod;
		processVic2CulturesFile(theConfiguration.getVic2Path() + "/mod/" + mod + "/common/cultures.txt");
	}

	processVic2CulturesFile(theConfiguration.getVic2Path() + "/common/cultures.txt");

	processNamesFile();
	if (theConfiguration.getDebug())
	{
		checkForNames();
	}

	return std::make_unique<Names>(std::move(maleNames),
		 std::move(femaleNames),
		 std::move(surnames),
		 std::move(femaleSurnames),
		 std::move(callsigns),
		 std::move(carCompanyNames),
		 std::move(weaponCompanyNames),
		 std::move(aircraftCompanyNames),
		 std::move(navalCompanyNames),
		 std::move(industryCompanyNames),
		 std::move(electronicCompanyNames),
		 std::move(intelligenceAgencyNames));
}


void HoI4::Names::Factory::processVic2CulturesFile(const std::string& filename)
{
	clearRegisteredKeywords();
	registerRegex("[A-Za-z0-9\\_]+", [this](const std::string& unused, std::istream& theStream) {
		const cultureGroup theGroup(theStream);
		for (auto& newMaleNameMapping: theGroup.getMaleNames())
		{
			addNamesToMap(maleNames, newMaleNameMapping.first, std::move(newMaleNameMapping.second));
		}
		for (auto& newSurnameMapping: theGroup.getSurnames())
		{
			addNamesToMap(surnames, newSurnameMapping.first, std::move(newSurnameMapping.second));
		}
	});

	parseFile(filename);
}


void HoI4::Names::Factory::processNamesFile()
{
	clearRegisteredKeywords();
	registerRegex("[A-Za-z0-9\\_]+", [this](const std::string& cultureName, std::istream& theStream) {
		culture newCulture(theStream);
		addNamesToMap(maleNames, cultureName, newCulture.takeMaleNames());
		addNamesToMap(femaleNames, cultureName, newCulture.takeFemaleNames());
		addNamesToMap(surnames, cultureName, newCulture.takeSurnames());
		addNamesToMap(femaleSurnames, cultureName, newCulture.takeFemaleSurnames());
		addNamesToMap(callsigns, cultureName, newCulture.takeCallsigns());
		addNamesToMap(carCompanyNames, cultureName, newCulture.takeCarCompanies());
		addNamesToMap(weaponCompanyNames, cultureName, newCulture.takeWeaponCompanies());
		addNamesToMap(aircraftCompanyNames, cultureName, newCulture.takeAircraftCompanies());
		addNamesToMap(navalCompanyNames, cultureName, newCulture.takeNavalCompanies());
		addNamesToMap(industryCompanyNames, cultureName, newCulture.takeIndustryCompanies());
		addNamesToMap(electronicCompanyNames, cultureName, newCulture.takeElectronicCompanies());
		addNamesToMap(intelligenceAgencyNames, cultureName, newCulture.takeIntelligenceAgencies());
	});

	parseFile("names.txt");
}


void HoI4::Names::Factory::addNamesToMap(std::map<std::string, std::vector<std::string>>& map,
	 const std::string& culture,
	 std::vector<std::string>&& newNames) const
{
	if (auto mapping = map.find(culture); mapping != map.end())
	{
		for (const auto& newName: newNames)
		{
			if (std::none_of(mapping->second.begin(), mapping->second.end(), [newName](const std::string& oldName) {
					 return oldName == newName;
				 }))
			{
				mapping->second.push_back(newName);
			}
		}
	}
	else
	{
		map.insert(make_pair(culture, newNames));
	}
}


void HoI4::Names::Factory::checkForNames()
{
	for (const auto& maleNamesMapping: maleNames)
	{
		auto culture = maleNamesMapping.first;

		if (femaleNames.find(culture) == femaleNames.end())
		{
			Log(LogLevel::Warning) << "No female names for " << culture;
		}
		// female surnames being missing is a common and acceptable case
		if (callsigns.find(culture) == callsigns.end())
		{
			Log(LogLevel::Warning) << "No callsigns for " << culture;
		}
		if (carCompanyNames.find(culture) == carCompanyNames.end())
		{
			Log(LogLevel::Warning) << "No car companies for " << culture;
		}
		if (weaponCompanyNames.find(culture) == weaponCompanyNames.end())
		{
			Log(LogLevel::Warning) << "No weapon companies for " << culture;
		}
		if (aircraftCompanyNames.find(culture) == aircraftCompanyNames.end())
		{
			Log(LogLevel::Warning) << "No aircraft companies for " << culture;
		}
		if (navalCompanyNames.find(culture) == navalCompanyNames.end())
		{
			Log(LogLevel::Warning) << "No naval companies for " << culture;
		}
		if (industryCompanyNames.find(culture) == industryCompanyNames.end())
		{
			Log(LogLevel::Warning) << "No industry companies for " << culture;
		}
		if (electronicCompanyNames.find(culture) == electronicCompanyNames.end())
		{
			Log(LogLevel::Warning) << "No electronic companies for " << culture;
		}
		if (intelligenceAgencyNames.find(culture) == intelligenceAgencyNames.end())
		{
			Log(LogLevel::Warning) << "No intelligence agencies for " << culture;
		}
	}
}


std::optional<std::vector<std::string>> HoI4::Names::getMaleNames(const std::string& culture) const
{
	if (const auto& namesItr = maleNames.find(culture); namesItr != maleNames.end())
	{
		return namesItr->second;
	}

	return std::nullopt;
}


std::optional<std::vector<std::string>> HoI4::Names::getFemaleNames(const std::string& culture) const
{
	if (const auto& namesItr = femaleNames.find(culture); namesItr != femaleNames.end())
	{
		return namesItr->second;
	}

	return std::nullopt;
}


std::optional<std::vector<std::string>> HoI4::Names::getSurnames(const std::string& culture) const
{
	if (const auto& namesItr = surnames.find(culture); namesItr != surnames.end())
	{
		return namesItr->second;
	}

	return std::nullopt;
}


std::optional<std::vector<std::string>> HoI4::Names::getFemaleSurnames(const std::string& culture) const
{
	if (const auto& namesItr = femaleSurnames.find(culture); namesItr != femaleSurnames.end())
	{
		return namesItr->second;
	}

	return std::nullopt;
}


std::optional<std::vector<std::string>> HoI4::Names::getCallsigns(const std::string& culture) const
{
	if (const auto& namesItr = callsigns.find(culture); namesItr != callsigns.end())
	{
		return namesItr->second;
	}

	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getMaleName(const std::string& culture)
{
	if (auto names = getMaleNames(culture); names && !names->empty())
	{
		const std::uniform_int_distribution<int> generator(0, names->size() - 1);
		return (*names)[generator(rng)];
	}

	Log(LogLevel::Warning) << "No male name could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getFemaleName(const std::string& culture)
{
	if (auto names = getFemaleNames(culture); names && !names->empty())
	{
		const std::uniform_int_distribution<int> generator(0, names->size() - 1);
		return (*names)[generator(rng)];
	}

	Log(LogLevel::Warning) << "No female name could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getSurname(const std::string& culture)
{
	if (auto names = getSurnames(culture); names && !names->empty())
	{
		const std::uniform_int_distribution<int> generator(0, names->size() - 1);
		return (*names)[generator(rng)];
	}

	Log(LogLevel::Warning) << "No surname could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getFemaleSurname(const std::string& culture)
{
	if (auto names = getFemaleSurnames(culture); names && !names->empty())
	{
		const std::uniform_int_distribution<int> generator(0, names->size() - 1);
		return (*names)[generator(rng)];
	}

	Log(LogLevel::Warning) << "No female surname could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getCallsign(const std::string& culture)
{
	if (auto names = getCallsigns(culture); names && !names->empty())
	{
		const std::uniform_int_distribution<int> generator(0, names->size() - 1);
		return (*names)[generator(rng)];
	}

	Log(LogLevel::Warning) << "No callsign could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::takeCarCompanyName(const std::string& culture)
{
	return takeCompanyName(carCompanyNames, culture);
}


std::optional<std::string> HoI4::Names::takeWeaponCompanyName(const std::string& culture)
{
	return takeCompanyName(weaponCompanyNames, culture);
}


std::optional<std::string> HoI4::Names::takeAircraftCompanyName(const std::string& culture)
{
	return takeCompanyName(aircraftCompanyNames, culture);
}


std::optional<std::string> HoI4::Names::takeNavalCompanyName(const std::string& culture)
{
	return takeCompanyName(navalCompanyNames, culture);
}


std::optional<std::string> HoI4::Names::takeIndustryCompanyName(const std::string& culture)
{
	return takeCompanyName(industryCompanyNames, culture);
}


std::optional<std::string> HoI4::Names::takeElectronicCompanyName(const std::string& culture)
{
	return takeCompanyName(electronicCompanyNames, culture);
}


std::optional<std::string> HoI4::Names::takeCompanyName(std::map<std::string, std::vector<std::string>>& companyNames,
	 const std::string& culture)
{
	if (auto namesItr = companyNames.find(culture); namesItr != companyNames.end())
	{
		std::vector<std::string> companies = namesItr->second;
		if (companies.size() > 0)
		{
			const std::uniform_int_distribution<int> generator(0, companies.size() - 1);
			auto company = companies[generator(rng)];
			for (std::vector<std::string>::iterator itr = companyNames[culture].begin();
				  itr != companyNames[culture].end();
				  ++itr)
			{
				if (*itr == company)
				{
					companyNames[culture].erase(itr);
					return company;
				}
			}
		}
	}

	return {};
}


std::optional<std::string> HoI4::Names::takeIntelligenceAgencyName(const std::string& culture)
{
	if (auto namesItr = intelligenceAgencyNames.find(culture); namesItr != intelligenceAgencyNames.end())
	{
		std::vector<std::string> agencies = namesItr->second;
		if (!agencies.empty())
		{
			const std::uniform_int_distribution<int> generator(0, agencies.size() - 1);
			auto agency = agencies[generator(rng)];
			for (std::vector<std::string>::iterator itr = intelligenceAgencyNames[culture].begin();
				  itr != intelligenceAgencyNames[culture].end();
				  ++itr)
			{
				if (*itr == agency)
				{
					intelligenceAgencyNames[culture].erase(itr);
					return agency;
				}
			}
		}
	}

	return std::nullopt;
}