#include "World.h"
#include "../Configuration.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/MergeRules.h"
#include "../Mappers/Provinces/ProvinceMapper.h"
#include "CommonCountryData.h"
#include "Country.h"
#include "Diplomacy.h"
#include "Inventions.h"
#include "Issues/Issues.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "Party.h"
#include "Province.h"
#include "State.h"
#include "Vic2Localisations.h"
#include <fstream>



Vic2::World::World(const std::string& filename,
	 const mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	theLocalisations = Localisations::Parser{}.importLocalisations(theConfiguration);
	theCultureGroups.init(theConfiguration);
	Issues theIssues = Issues::Parser{}.importIssues(theConfiguration);
	theStateDefinitions = StateDefinitions::Parser{}.parseStateDefinitions(theConfiguration);
	inventions theInventions(theConfiguration);

	std::vector<int> GPIndexes;
	registerKeyword(std::regex("great_nations"), [&GPIndexes, this](const std::string& unused, std::istream& theStream) {
		commonItems::intList indexList(theStream);
		GPIndexes = indexList.getInts();
	});

	registerKeyword(std::regex("\\d+"), [this, &theIssues](const std::string& provinceID, std::istream& theStream) {
		provinces[stoi(provinceID)] = new Vic2::Province(provinceID, theStream, theIssues);
	});

	std::vector<std::string> tagsInOrder;
	tagsInOrder.push_back(""); // REB (first country is index 1
	registerKeyword(std::regex("[A-Z]{3}"),
		 [&tagsInOrder, &theInventions, this](const std::string& countryTag, std::istream& theStream) {
			 countries[countryTag] =
				  new Country(countryTag, theStream, theInventions, theCultureGroups, *theStateDefinitions);
			 tagsInOrder.push_back(countryTag);
		 });
	registerKeyword(std::regex("[A-Z][0-9]{2}"),
		 [&tagsInOrder, &theInventions, this](const std::string& countryTag, std::istream& theStream) {
			 countries[countryTag] =
				  new Country(countryTag, theStream, theInventions, theCultureGroups, *theStateDefinitions);
			 tagsInOrder.push_back(countryTag);
		 });
	registerKeyword(std::regex("diplomacy"), [this](const std::string& top, std::istream& theStream) {
		diplomacy = new Vic2::Diplomacy(theStream);
	});

	std::vector<War> wars;
	registerKeyword(std::regex("active_war"), [&wars](const std::string& unused, std::istream& theStream) {
		War newWar(theStream);
		wars.push_back(newWar);
	});

	registerKeyword(std::regex("[A-Za-z0-9_]+"), commonItems::ignoreItem);


	LOG(LogLevel::Info) << "* Importing V2 save *";
	parseFile(filename);


	LOG(LogLevel::Info) << "Building world";
	setGreatPowerStatus(GPIndexes, tagsInOrder);
	setProvinceOwners();
	addProvinceCoreInfoToCountries();
	if (theConfiguration.getRemoveCores())
	{
		removeSimpleLandlessNations();
	}
	determineEmployedWorkers();
	overallMergeNations();
	removeEmptyNations();
	determinePartialStates(*theStateDefinitions);
	addWarsToCountries(wars);
	if (diplomacy == nullptr)
	{
		diplomacy = new Vic2::Diplomacy();
	}
	readCountryFiles(theConfiguration);
	setLocalisations(*theLocalisations);
	handleMissingCountryCultures();

	checkAllProvincesMapped(provinceMapper);
}


void Vic2::World::setGreatPowerStatus(const std::vector<int>& GPIndexes, const std::vector<std::string>& tagsInOrder)
{
	for (auto index: GPIndexes)
	{
		auto tag = tagsInOrder.at(index);
		greatPowers.push_back(tag);
	}
}


void Vic2::World::setProvinceOwners()
{
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
			LOG(LogLevel::Warning) << "Trying to set " << province.second->getOwner() << " as owner of " << province.first
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
	for (auto province: provinces)
	{
		auto provinceCores = province.second->getCores();
		for (auto coreCountryString: provinceCores)
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
	for (auto country: countries)
	{
		if (country.second->getProvinces().size() > 0)
		{
			continue;
		}

		std::vector<Vic2::Province*> coresToKeep;
		for (auto core: country.second->getCores())
		{
			if (shouldCoreBeRemoved(core, country.second))
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
			std::vector<Province*> emptyCores;
			country.second->replaceCores(emptyCores);
		}
	}
}


bool Vic2::World::shouldCoreBeRemoved(const Province* core, const Country* country) const
{
	if (core->getOwner().empty())
	{
		return true;
	}

	auto owner = countries.find(core->getOwner());
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
	else if (core->getPercentageWithCultures(country->getAcceptedCultures()) < 0.25)
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
	for (auto country: countries)
	{
		country.second->determineEmployedWorkers();
	}
}


void Vic2::World::removeEmptyNations()
{
	std::map<std::string, Country*> newCountries;

	for (auto country: countries)
	{
		if (!country.second->isEmpty())
		{
			newCountries.insert(country);
		}
	}

	countries.swap(newCountries);
}


void Vic2::World::determinePartialStates(const Vic2::StateDefinitions& theStateDefinitions)
{
	for (auto country: countries)
	{
		for (auto state: country.second->getStates())
		{
			state->determineIfPartialState(theStateDefinitions);
		}
	}
}


void Vic2::World::addWarsToCountries(const std::vector<War>& wars)
{
	for (auto war: wars)
	{
		auto warStarter = countries.find(war.getOriginalAttacker());
		if (warStarter == countries.end())
		{
			continue;
		}
		warStarter->second->addWar(war);

		for (auto participant: war.getAttackers())
		{
			auto participantCountry = countries.find(participant);
			if (participantCountry == countries.end())
			{
				continue;
			}
			participantCountry->second->setAtWar();
		}

		for (auto participant: war.getDefenders())
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
	bool countriesDotTxtRead = false;

	for (auto vic2Mod: theConfiguration.getVic2Mods())
	{
		if (processCountriesDotTxt(theConfiguration.getVic2Path() + "/mod/" + vic2Mod + "/common/countries.txt",
				  vic2Mod,
				  theConfiguration))
		{
			countriesDotTxtRead = true;
		}
	}
	if (!countriesDotTxtRead)
	{
		if (!processCountriesDotTxt(theConfiguration.getVic2Path() + "/common/countries.txt", "", theConfiguration))
		{
			LOG(LogLevel::Error) << "Could not open " << theConfiguration.getVic2Path() + "/common/countries.txt";
			exit(-1);
		}
	}
}


bool Vic2::World::processCountriesDotTxt(const std::string& countryListFile,
	 const std::string& mod,
	 const Configuration& theConfiguration)
{
	std::ifstream V2CountriesInput(countryListFile);
	if (!V2CountriesInput.is_open())
	{
		return false;
	}

	while (!V2CountriesInput.eof())
	{
		std::string line;
		getline(V2CountriesInput, line);
		if (shouldLineBeSkipped(line))
		{
			continue;
		}

		std::string tag = line.substr(0, 3);
		std::string countryFileName = extractCountryFileName(line);
		commonCountryData countryData(countryFileName, mod, theConfiguration);
		if (countries.find(tag) != countries.end())
		{
			countries[tag]->setColor(countryData.getColor());
			countries[tag]->setShipNames(countryData.getUnitNames());
		}
		for (auto party: countryData.getParties())
		{
			parties.emplace_back(party);
		}
	}

	V2CountriesInput.close();
	return true;
}


bool Vic2::World::shouldLineBeSkipped(const std::string& line) const
{
	return ((line[0] == '#') || (line.size() < 3) || (line.substr(0, 12) == "dynamic_tags"));
}


std::string Vic2::World::extractCountryFileName(const std::string& countryFileLine) const
{
	std::string countryFileName;
	int start = countryFileLine.find_first_of('/');
	int size = countryFileLine.find_last_of('\"') - start;
	countryFileName = countryFileLine.substr(start, size);

	return countryFileName;
}


void Vic2::World::overallMergeNations()
{
	LOG(LogLevel::Info) << "Merging nations";
	MergeRules theMergeRules;
	for (auto rule: theMergeRules.getRules())
	{
		mergeNations(rule.first, rule.second);
	}
}


void Vic2::World::mergeNations(const std::string& masterTag, const std::vector<std::string>& slaveTags)
{
	auto master = getCountry(masterTag);
	if (master)
	{
		for (auto slaveTag: slaveTags)
		{
			auto slave = getCountry(slaveTag);
			if (slave)
			{
				(*master)->eatCountry(*slave);
			}
			countries.erase(slaveTag);
		}
	}
}


std::optional<Vic2::Country*> Vic2::World::getCountry(const std::string& tag) const
{
	auto countryItr = countries.find(tag);
	if (countryItr != countries.end())
	{
		return countryItr->second;
	}
	else
	{
		return {};
	}
}


void Vic2::World::setLocalisations(Localisations& vic2Localisations)
{
	for (auto country: countries)
	{
		country.second->setLocalisationNames(vic2Localisations);
		country.second->setLocalisationAdjectives(vic2Localisations);
	}
}


void Vic2::World::handleMissingCountryCultures()
{
	for (auto country: countries)
	{
		country.second->handleMissingCulture(theCultureGroups);
	}
}


std::optional<const Vic2::Province*> Vic2::World::getProvince(int provNum) const
{
	auto provinceItr = provinces.find(provNum);
	if (provinceItr != provinces.end())
	{
		return provinceItr->second;
	}
	else
	{
		return {};
	}
}


void Vic2::World::checkAllProvincesMapped(const mappers::ProvinceMapper& provinceMapper) const
{
	for (auto province: provinces)
	{
		auto mapping = provinceMapper.getVic2ToHoI4ProvinceMapping(province.first);
		if (!mapping)
		{
			LOG(LogLevel::Warning) << "No mapping for Vic2 province " << province.first;
		}
	}
}