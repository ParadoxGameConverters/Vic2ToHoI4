#include "Names.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "CultureGroupNames.h"
#include "CultureNames.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



std::unique_ptr<HoI4::Names> HoI4::Names::Factory::getNames(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tParsing names";

	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		if (commonItems::DoesFileExist(
				  theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt"))
		{
			Log(LogLevel::Debug) << "Reading mod cultures from " << mod.getName();
			processVic2CulturesFile(theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt");
		}
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
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		CultureGroupNames theGroup(theStream);
		for (auto& newMaleNameMapping: theGroup.takeMaleNames())
		{
			addNamesToMap(maleNames, newMaleNameMapping.first, std::move(newMaleNameMapping.second));
		}
		for (auto& newSurnameMapping: theGroup.takeSurnames())
		{
			addNamesToMap(surnames, newSurnameMapping.first, std::move(newSurnameMapping.second));
		}
	});

	parseFile(filename);
}


void HoI4::Names::Factory::processNamesFile()
{
	clearRegisteredKeywords();
	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureName, std::istream& theStream) {
		CultureNames cultureNames(theStream);
		addNamesToMap(maleNames, cultureName, cultureNames.takeMaleNames());
		addNamesToMap(femaleNames, cultureName, cultureNames.takeFemaleNames());
		addNamesToMap(surnames, cultureName, cultureNames.takeSurnames());
		addNamesToMap(femaleSurnames, cultureName, cultureNames.takeFemaleSurnames());
		addNamesToMap(callsigns, cultureName, cultureNames.takeCallsigns());
		addNamesToMap(carCompanyNames, cultureName, cultureNames.takeCarCompanies());
		addNamesToMap(weaponCompanyNames, cultureName, cultureNames.takeWeaponCompanies());
		addNamesToMap(aircraftCompanyNames, cultureName, cultureNames.takeAircraftCompanies());
		addNamesToMap(navalCompanyNames, cultureName, cultureNames.takeNavalCompanies());
		addNamesToMap(industryCompanyNames, cultureName, cultureNames.takeIndustryCompanies());
		addNamesToMap(electronicCompanyNames, cultureName, cultureNames.takeElectronicCompanies());
		addNamesToMap(intelligenceAgencyNames, cultureName, cultureNames.takeIntelligenceAgencies());
	});

	parseFile("Configurables/names.txt");
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

		if (auto names = femaleNames.find(culture); (names == femaleNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No female names for " << culture;
		}
		// female surnames being missing is a common and acceptable case
		if (auto names = callsigns.find(culture); (names == callsigns.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No callsigns for " << culture;
		}
		if (auto names = carCompanyNames.find(culture); (names == carCompanyNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No car companies for " << culture;
		}
		if (auto names = weaponCompanyNames.find(culture); (names == weaponCompanyNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No weapon companies for " << culture;
		}
		if (auto names = aircraftCompanyNames.find(culture);
			 (names == aircraftCompanyNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No aircraft companies for " << culture;
		}
		if (auto names = navalCompanyNames.find(culture); (names == navalCompanyNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No naval companies for " << culture;
		}
		if (auto names = industryCompanyNames.find(culture);
			 (names == industryCompanyNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No industry companies for " << culture;
		}
		if (auto names = electronicCompanyNames.find(culture);
			 (names == electronicCompanyNames.end()) || names->second.empty())
		{
			Log(LogLevel::Warning) << "No electronic companies for " << culture;
		}
		if (auto names = intelligenceAgencyNames.find(culture);
			 (names == intelligenceAgencyNames.end()) || names->second.empty())
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
		return names->at(std::uniform_int_distribution<int>{0, static_cast<int>(names->size() - 1)}(generator));
	}

	Log(LogLevel::Warning) << "No male name could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getFemaleName(const std::string& culture)
{
	if (auto names = getFemaleNames(culture); names && !names->empty())
	{
		return names->at(std::uniform_int_distribution<int>{0, static_cast<int>(names->size() - 1)}(generator));
	}

	Log(LogLevel::Warning) << "No female name could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getSurname(const std::string& culture)
{
	if (auto names = getSurnames(culture); names && !names->empty())
	{
		return names->at(std::uniform_int_distribution<int>{0, static_cast<int>(names->size() - 1)}(generator));
	}

	Log(LogLevel::Warning) << "No surname could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getFemaleSurname(const std::string& culture)
{
	if (auto names = getFemaleSurnames(culture); names && !names->empty())
	{
		return names->at(std::uniform_int_distribution<int>{0, static_cast<int>(names->size() - 1)}(generator));
	}

	Log(LogLevel::Warning) << "No female surname could be found for " << culture;
	return std::nullopt;
}


std::optional<std::string> HoI4::Names::getCallsign(const std::string& culture)
{
	if (auto names = getCallsigns(culture); names && !names->empty())
	{
		return names->at(std::uniform_int_distribution<int>{0, static_cast<int>(names->size() - 1)}(generator));
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
		if (auto& companies = namesItr->second; !companies.empty())
		{
			auto companiesIterator = companies.begin();
			std::advance(companiesIterator,
				 std::uniform_int_distribution<int>{0, static_cast<int>(companies.size() - 1)}(generator));
			auto company = *companiesIterator;
			companies.erase(companiesIterator);
			return company;
		}
	}

	return std::nullopt;
}


std::optional<std::string> HoI4::Names::takeIntelligenceAgencyName(const std::string& culture)
{
	if (auto namesItr = intelligenceAgencyNames.find(culture); namesItr != intelligenceAgencyNames.end())
	{
		if (auto& agencies = namesItr->second; !agencies.empty())
		{
			auto agenciesIterator = agencies.begin();
			std::advance(agenciesIterator,
				 std::uniform_int_distribution<int>{0, static_cast<int>(agencies.size() - 1)}(generator));
			auto agency = *agenciesIterator;
			agencies.erase(agenciesIterator);
			return agency;
		}
	}

	return std::nullopt;
}