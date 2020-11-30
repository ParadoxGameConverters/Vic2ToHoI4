#include "World.h"
#include "Configuration.h"
#include "Countries/CommonCountriesDataFactory.h"
#include "Countries/Country.h"
#include "Countries/CountryFactory.h"
#include "Countries/CommonCountryData.h"
#include "Ai/Vic2AI.h"
#include "Culture/CultureGroupsFactory.h"
#include "Date.h"
#include "Diplomacy/DiplomacyFactory.h"
#include "Issues/Issues.h"
#include "Issues/IssuesFactory.h"
#include "Localisations/LocalisationsFactory.h"
#include "Localisations/Vic2Localisations.h"
#include "Log.h"
#include "Mappers/MergeRules.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "ParserHelpers.h"
#include "Pops/PopFactory.h"
#include "Provinces/Province.h"
#include "Provinces/ProvinceFactory.h"
#include "States/State.h"
#include "States/StateDefinitionsFactory.h"
#include "States/StateLanguageCategoriesFactory.h"
#include "Wars/WarFactory.h"
#include <fstream>



Vic2::World::World(const mappers::ProvinceMapper& provinceMapper, const Configuration& theConfiguration):
	 theLocalisations(Localisations::Factory{}.importLocalisations(theConfiguration))
{
	auto theIssues = Issues::Factory{}.getIssues(theConfiguration.getVic2Path());
	theStateDefinitions = StateDefinitions::Factory{}.getStateDefinitions(theConfiguration);
	auto popFactory = std::make_unique<Pop::Factory>(*theIssues);
	Province::Factory provinceFactory(std::move(popFactory));
	War::Factory warFactory;
	Country::Factory countryFactory(theConfiguration, *theStateDefinitions);

	const auto [commonCountriesData, allParties] = Vic2::importCommonCountriesData(theConfiguration);

	registerKeyword("date", [](const std::string& unused, std::istream& theStream) {
		const date theDate{commonItems::singleString{theStream}.getString()};
		Log(LogLevel::Info) << "The date is " << theDate;
	});

	std::vector<int> GPIndexes;
	registerKeyword("great_nations", [&GPIndexes, this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList indexList(theStream);
		GPIndexes = indexList.getInts();
	});

	registerRegex(R"(\d+)", [this, &provinceFactory](const std::string& provinceID, std::istream& theStream) {
		try
		{
			const auto provinceNum = std::stoi(provinceID);
			provinces[provinceNum] = provinceFactory.getProvince(provinceNum, theStream);
		}
		catch (std::exception&)
		{
			Log(LogLevel::Warning) << "Invalid province number " << provinceID;
		}
	});

	std::vector<std::string> tagsInOrder;
	tagsInOrder.push_back(""); // REB (first country is index 1)
	registerRegex("[A-Z][A-Z0-9]{2}",
		 [&tagsInOrder, &commonCountriesData, &allParties, &countryFactory, this](const std::string& countryTag,
			  std::istream& theStream) {
			 if (const auto commonCountryData = commonCountriesData.find(countryTag);
				  commonCountryData != commonCountriesData.end())
			 {
				 countries[countryTag] =
					  countryFactory.createCountry(countryTag, theStream, commonCountryData->second, allParties);
				 tagsInOrder.push_back(countryTag);
			 }
		 });
	registerKeyword("diplomacy", [this](const std::string& unused, std::istream& theStream) {
		diplomacy = Diplomacy::Factory{}.getDiplomacy(theStream);
	});

	std::vector<War> wars;
	registerKeyword("active_war", [&wars, &warFactory](const std::string& unused, std::istream& theStream) {
		wars.push_back(*warFactory.getWar(theStream));
	});

	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);


	Log(LogLevel::Progress) << "15%";
	Log(LogLevel::Info) << "*** Importing V2 save ***";
	parseFile(theConfiguration.getInputFile());

	Log(LogLevel::Progress) << "21%";
	Log(LogLevel::Info) << "Building Vic2 world";
	setGreatPowerStatus(GPIndexes, tagsInOrder);
	setProvinceOwners();
	limitCommanders();
	addProvinceCoreInfoToCountries();
	if (theConfiguration.getRemoveCores())
	{
		removeSimpleLandlessNations();
	}
	determineEmployedWorkers();
	overallMergeNations(theConfiguration.getDebug());
	removeEmptyNations();
	addWarsToCountries(wars);
	setLocalisations(*theLocalisations);

	checkAllProvincesMapped(provinceMapper);
	consolidateConquerStrategies();
}


void Vic2::World::setGreatPowerStatus(const std::vector<int>& GPIndexes, const std::vector<std::string>& tagsInOrder)
{
	Log(LogLevel::Info) << "\tSetting Great Power statuses";
	for (auto index: GPIndexes)
	{
		const auto& tag = tagsInOrder.at(index);
		greatPowers.push_back(tag);
	}
}


void Vic2::World::setProvinceOwners()
{
	Log(LogLevel::Info) << "\tAssigning province owners";
	for (auto province: provinces)
	{
		if (province.second->getOwner() == "")
		{
			continue;
		}

		if (auto country = countries.find(province.second->getOwner()); country != countries.end())
		{
			country->second->addProvince(province);
			province.second->setOwner(country->first);
		}
		else
		{
			Log(LogLevel::Warning) << "Trying to set " << province.second->getOwner() << " as owner of " << province.first
										  << ", but country does not exist.";
		}
	}
	for (auto country: countries)
	{
		country.second->putProvincesInStates();
	}
}


void Vic2::World::limitCommanders()
{
	for (auto& [unused, country]: countries)
	{
		country->limitCommanders();
	}
}



void Vic2::World::addProvinceCoreInfoToCountries()
{
	Log(LogLevel::Info) << "\tAssigning cores to countries";
	for (const auto& province: provinces)
	{
		auto provinceCores = province.second->getCores();
		for (const auto& coreCountryString: provinceCores)
		{
			auto coreCountry = countries.find(coreCountryString);
			if (coreCountry != countries.end())
			{
				coreCountry->second->addCore(province.second);
			}
		}
	}
}


void Vic2::World::removeSimpleLandlessNations()
{
	Log(LogLevel::Info) << "\tRemoving simple landless nations";
	for (auto country: countries)
	{
		if (country.second->hasLand())
		{
			continue;
		}

		std::vector<std::shared_ptr<Province>> coresToKeep;
		for (auto core: country.second->getCores())
		{
			if (shouldCoreBeRemoved(*core, *country.second))
			{
				core->removeCore(country.first);
			}
			else
			{
				coresToKeep.push_back(core);
			}
		}
		country.second->replaceCores(coresToKeep);

		if (!country.second->hasCoreOnCapital())
		{
			country.second->replaceCores(std::vector<std::shared_ptr<Province>>{});
		}
	}
}


bool Vic2::World::shouldCoreBeRemoved(const Province& core, const Country& country) const
{
	if (core.getOwner().empty())
	{
		return true;
	}

	const auto owner = countries.find(core.getOwner());
	if (owner == countries.end())
	{
		return true;
	}
	else if (country.getPrimaryCulture() == owner->second->getPrimaryCulture())
	{
		return true;
	}
	else if (owner->second->isAnAcceptedCulture(owner->second->getPrimaryCulture()))
	{
		return true;
	}
	else if (core.getPercentageWithCultures(country.getAcceptedCultures()) < 0.25)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Vic2::World::determineEmployedWorkers()
{
	Log(LogLevel::Info) << "\tFinding employed workers";
	for (auto country: countries)
	{
		country.second->determineEmployedWorkers();
	}
}


void Vic2::World::removeEmptyNations()
{
	Log(LogLevel::Info) << "\tRemoving empty nations";
	std::map<std::string, std::shared_ptr<Country>> newCountries;

	for (auto& [tag, country]: countries)
	{
		if (!country->isEmpty())
		{
			newCountries.insert(std::make_pair(tag, country));
		}
	}

	countries.swap(newCountries);
}


void Vic2::World::addWarsToCountries(const std::vector<War>& wars)
{
	Log(LogLevel::Info) << "\tReconstructing wars";
	for (const auto& war: wars)
	{
		auto warStarter = countries.find(war.getOriginalAttacker());
		if (warStarter == countries.end())
		{
			continue;
		}
		warStarter->second->addWar(war);

		for (const auto& participant: war.getAttackers())
		{
			auto participantCountry = countries.find(participant);
			if (participantCountry == countries.end())
			{
				continue;
			}
			participantCountry->second->setAtWar();
		}

		for (const auto& participant: war.getDefenders())
		{
			auto participantCountry = countries.find(participant);
			if (participantCountry == countries.end())
			{
				continue;
			}
			participantCountry->second->setAtWar();
		}
	}
}


void Vic2::World::overallMergeNations(bool debug)
{
	Log(LogLevel::Info) << "\tMerging nations";
	const MergeRules theMergeRules;
	for (const auto& rule: theMergeRules.getRules())
	{
		mergeNations(rule.first, rule.second, debug);
	}
}


void Vic2::World::mergeNations(const std::string& masterTag, const std::vector<std::string>& slaveTags, bool debug)
{
	auto master = getCountry(masterTag);
	if (master)
	{
		for (const auto& slaveTag: slaveTags)
		{
			auto slave = getCountry(slaveTag);
			if (slave)
			{
				(*master)->eatCountry(**slave, debug);
			}
			countries.erase(slaveTag);
		}
	}
}


std::optional<std::shared_ptr<Vic2::Country>> Vic2::World::getCountry(const std::string& tag) const
{
	if (const auto countryItr = countries.find(tag); countryItr != countries.end())
	{
		return countryItr->second;
	}
	else
	{
		return std::nullopt;
	}
}


void Vic2::World::setLocalisations(Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tSetting localisations";
	checkStateCategories();
	for (auto country: countries)
	{
		country.second->setLocalisationNames(vic2Localisations);
		country.second->setLocalisationAdjectives(vic2Localisations);
	}
}


void Vic2::World::checkStateCategories()
{
	const auto stateLanguageCategories = StateLanguageCategories::Factory{}.getCategories();
	for (auto country: countries)
	{
		for (auto& state: country.second->getModifiableStates())
		{
			const auto category = stateLanguageCategories->getStateCategory(state.getStateID());
			if (category)
			{
				state.setLanguageCategory(*category);
			}
			else
			{
				Log(LogLevel::Warning) << state.getStateID() << " was not in any language category.";
			}
		}
	}
}


std::optional<const std::shared_ptr<Vic2::Province>> Vic2::World::getProvince(const int provNum) const
{
	if (const auto provinceItr = provinces.find(provNum); provinceItr != provinces.end())
	{
		return provinceItr->second;
	}
	else
	{
		return std::nullopt;
	}
}


void Vic2::World::checkAllProvincesMapped(const mappers::ProvinceMapper& provinceMapper) const
{
	Log(LogLevel::Info) << "\tChecking all provinces are mapped";
	for (const auto& province: provinces)
	{
		const auto mapping = provinceMapper.getVic2ToHoI4ProvinceMapping(province.first);
		if (!mapping)
		{
			Log(LogLevel::Warning) << "No mapping for Vic2 province " << province.first;
		}
	}
}

void Vic2::World::consolidateConquerStrategies()
{
	for (auto [unused, country]: countries)
	{
		country->consolidateConquerStrategies(provinces);
	}
}