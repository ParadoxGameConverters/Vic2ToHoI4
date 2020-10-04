#include "World.h"
#include "../Configuration.h"
#include "../Mappers/MergeRules.h"
#include "../Mappers/Provinces/ProvinceMapper.h"
#include "CommonCountryData.h"
#include "Country.h"
#include "Culture/CultureGroupsFactory.h"
#include "Date.h"
#include "Diplomacy/DiplomacyFactory.h"
#include "Diplomacy/RelationsFactory.h"
#include "Issues/Issues.h"
#include "Issues/IssuesFactory.h"
#include "Log.h"
#include "Military/UnitFactory.h"
#include "ParserHelpers.h"
#include "Politics/Party.h"
#include "Politics/PartyFactory.h"
#include "Pops/PopFactory.h"
#include "Provinces/Province.h"
#include "Provinces/ProvinceFactory.h"
#include "States/State.h"
#include "States/StateDefinitionsFactory.h"
#include "States/StateFactory.h"
#include "States/StateLanguageCategoriesFactory.h"
#include "Technology/Inventions.h"
#include "Technology/InventionsFactory.h"
#include "Vic2Localisations.h"
#include "Wars/WarFactory.h"
#include <fstream>



Vic2::World::World(const mappers::ProvinceMapper& provinceMapper, const Configuration& theConfiguration)
{
	theLocalisations = Localisations::Parser{}.importLocalisations(theConfiguration);
	theCultureGroups = CultureGroups::Factory{}.getCultureGroups(theConfiguration);
	auto theIssues = Issues::Factory{}.getIssues(theConfiguration.getVic2Path());
	theStateDefinitions = StateDefinitions::Factory{}.getStateDefinitions(theConfiguration);
	std::unique_ptr<Inventions> theInventions = Inventions::Factory{}.loadInventions(theConfiguration);
	auto popFactory = std::make_unique<Pop::Factory>(*theIssues);
	Province::Factory provinceFactory(std::move(popFactory));
	State::Factory stateFactory;
	War::Factory warFactory;
	Relations::Factory relationsFactory;
	Leader::Factory leaderFactory;
	Unit::Factory unitFactory;

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
	tagsInOrder.push_back(""); // REB (first country is index 1
	registerRegex("[A-Z][A-Z0-9]{2}",
		 [&tagsInOrder, &theInventions, &stateFactory, &relationsFactory, &leaderFactory, &unitFactory, this](
			  const std::string& countryTag,
			  std::istream& theStream) {
			 countries[countryTag] = new Country(countryTag,
				  theStream,
				  *theInventions,
				  *theCultureGroups,
				  *theStateDefinitions,
				  stateFactory,
				  relationsFactory,
				  leaderFactory,
				  unitFactory);
			 tagsInOrder.push_back(countryTag);
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
	addProvinceCoreInfoToCountries();
	if (theConfiguration.getRemoveCores())
	{
		removeSimpleLandlessNations();
	}
	determineEmployedWorkers();
	overallMergeNations(theConfiguration.getDebug());
	removeEmptyNations();
	addWarsToCountries(wars);
	readCountryFiles(theConfiguration);
	setLocalisations(*theLocalisations);
	handleMissingCountryCultures();

	checkAllProvincesMapped(provinceMapper);
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
		if (country.second->getProvinces().size() > 0)
		{
			continue;
		}

		std::vector<std::shared_ptr<Province>> coresToKeep;
		for (auto core: country.second->getCores())
		{
			if (shouldCoreBeRemoved(*core, country.second))
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


bool Vic2::World::shouldCoreBeRemoved(const Province& core, const Country* country) const
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
	else if (country->getPrimaryCulture() == owner->second->getPrimaryCulture())
	{
		return true;
	}
	else if (owner->second->isAnAcceptedCulture(owner->second->getPrimaryCulture()))
	{
		return true;
	}
	else if (core.getPercentageWithCultures(country->getAcceptedCultures()) < 0.25)
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
	std::map<std::string, Country*> newCountries;

	for (const auto& country: countries)
	{
		if (!country.second->isEmpty())
		{
			newCountries.insert(country);
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


void Vic2::World::readCountryFiles(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tReading country files";
	auto countriesDotTxtRead = false;

	for (const auto& vic2Mod: theConfiguration.getVic2Mods())
	{
		if (processCountriesDotTxt(
				  theConfiguration.getVic2ModPath() + "/" + vic2Mod.getDirectory() + "/common/countries.txt",
				  vic2Mod,
				  theConfiguration))
		{
			countriesDotTxtRead = true;
		}
	}
	if (!countriesDotTxtRead)
	{
		if (!processCountriesDotTxt(theConfiguration.getVic2Path() + "/common/countries.txt",
				  std::nullopt,
				  theConfiguration))
		{
			throw std::runtime_error("Could not open " + theConfiguration.getVic2Path() + "/common/countries.txt");
		}
	}
}


bool Vic2::World::processCountriesDotTxt(const std::string& countryListFile,
	 const std::optional<Vic2::Mod>& mod,
	 const Configuration& theConfiguration)
{
	std::ifstream V2CountriesInput(countryListFile);
	if (!V2CountriesInput.is_open())
	{
		return false;
	}

	std::vector<Party> parties;
	Party::Factory partyFactory;

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
		commonCountryData countryData(countryFileName, mod, theConfiguration, &partyFactory);
		if (countries.find(tag) != countries.end())
		{
			countries[tag]->setColor(countryData.getColor());
			countries[tag]->setShipNames(countryData.getUnitNames());
		}
		for (const auto& party: countryData.getParties())
		{
			parties.emplace_back(party);
		}
	}

	V2CountriesInput.close();

	for (auto& [unused, country]: countries)
	{
		country->setParties(parties);
	}

	return true;
}


bool Vic2::World::shouldLineBeSkipped(const std::string& line)
{
	return (line[0] == '#') || (line.size() < 3) || (line.substr(0, 12) == "dynamic_tags");
}


std::string Vic2::World::extractCountryFileName(const std::string& countryFileLine)
{
	const auto start = countryFileLine.find_first_of('/');
	const auto size = countryFileLine.find_last_of('\"') - start;

	return countryFileLine.substr(start, size);
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
				(*master)->eatCountry(*slave, debug);
			}
			countries.erase(slaveTag);
		}
	}
}


std::optional<Vic2::Country*> Vic2::World::getCountry(const std::string& tag) const
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
		for (auto& state: country.second->getStates())
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


void Vic2::World::handleMissingCountryCultures()
{
	Log(LogLevel::Info) << "\tHandling missing country cultures";
	for (auto country: countries)
	{
		country.second->handleMissingCulture(*theCultureGroups);
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