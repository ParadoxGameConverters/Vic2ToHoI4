#include "WorldFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "Mappers/MergeRules/MergeRules.h"
#include "Mappers/MergeRules/MergeRulesFactory.h"
#include "ParserHelpers.h"
#include "V2World/Countries/CommonCountriesDataFactory.h"
#include "V2World/Culture/CultureGroupsFactory.h"
#include "V2World/Issues/IssuesFactory.h"
#include "V2World/Localisations/LocalisationsFactory.h"
#include "V2World/Pops/PopFactory.h"
#include "V2World/States/StateDefinitionsFactory.h"
#include "V2World/States/StateLanguageCategoriesFactory.h"



Vic2::World::Factory::Factory(const Configuration& theConfiguration):
	 theCultureGroups(CultureGroups::Factory().getCultureGroups(theConfiguration)),
	 theIssues(Issues::Factory().getIssues(theConfiguration.getVic2Path())),
	 provinceFactory(std::make_unique<Province::Factory>(std::make_unique<PopFactory>(*theIssues))),
	 theStateDefinitions(StateDefinitions::Factory().getStateDefinitions(theConfiguration)),
	 countryFactory(std::make_unique<Country::Factory>(theConfiguration, *theStateDefinitions, theCultureGroups)),
	 stateLanguageCategories(StateLanguageCategories::Factory().getCategories()),
	 diplomacyFactory(std::make_unique<Diplomacy::Factory>())
{
	const auto [commonCountriesData_, allParties_] = importCommonCountriesData(theConfiguration);
	commonCountriesData = commonCountriesData_;
	allParties = allParties_;
	countriesData = CountriesData::Factory().importCountriesData(theConfiguration);

	registerKeyword("date", [this](std::istream& theStream) {
		world->theDate = std::make_unique<date>(date(commonItems::singleString{theStream}.getString()));
	});
	
	registerKeyword("great_nations", [this](std::istream& theStream) {
		greatPowerIndexes = commonItems::intList{theStream}.getInts();
	});
	registerRegex(R"(\d+)", [this](const std::string& provinceID, std::istream& theStream) {
		const auto provinceNum = std::stoi(provinceID); // the regex ensures the ID is always a valid number
		world->provinces[provinceNum] = provinceFactory->getProvince(provinceNum, theStream);
	});
	registerRegex("[A-Z][A-Z0-9]{2}", [this, theConfiguration](const std::string& countryTag, std::istream& theStream) {
		if (const auto commonCountryData = commonCountriesData.find(countryTag);
			 commonCountryData != commonCountriesData.end())
		{
			world->countries.emplace(countryTag,
				 *countryFactory->createCountry(countryTag,
					  theStream,
					  commonCountryData->second,
					  allParties,
					  *stateLanguageCategories,
					  theConfiguration.getPercentOfCommanders(),
					  countriesData->getCountryData(countryTag)));
			tagsInOrder.push_back(countryTag);
		}
		else
		{
			Log(LogLevel::Warning) << "Invalid tag " << countryTag;
			commonItems::ignoreItem(countryTag, theStream);
		}
	});
	registerKeyword("diplomacy", [this](std::istream& theStream) {
		world->diplomacy = diplomacyFactory->getDiplomacy(theStream);
	});
	registerKeyword("active_war", [this](std::istream& theStream) {
		wars.push_back(*warFactory.getWar(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::World> Vic2::World::Factory::importWorld(const Configuration& theConfiguration,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	Log(LogLevel::Progress) << "15%";
	Log(LogLevel::Info) << "*** Importing V2 save ***";

	greatPowerIndexes.clear();
	tagsInOrder.clear();
	tagsInOrder.emplace_back(""); // REB (first country is index 1)
	wars.clear();

	world = std::make_unique<World>();
	world->theStateDefinitions = StateDefinitions::Factory().getStateDefinitions(theConfiguration);
	world->theLocalisations = Localisations::Factory().importLocalisations(theConfiguration);
	parseFile(theConfiguration.getInputFile());
	if (!world->diplomacy)
	{
		Log(LogLevel::Warning) << "Vic2 save had no diplomacy section!";
		world->diplomacy = std::make_unique<Diplomacy>();
	}

	Log(LogLevel::Progress) << "21%";
	Log(LogLevel::Info) << "Building Vic2 world";
	setGreatPowerStatus();
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
	setLocalisations(*world->theLocalisations);
	checkAllProvincesMapped(provinceMapper);
	consolidateConquerStrategies();
	moveArmiesHome();
	removeBattles();

	return std::move(world);
}


void Vic2::World::Factory::setGreatPowerStatus()
{
	Log(LogLevel::Info) << "\tSetting Great Power statuses";
	for (auto index: greatPowerIndexes)
	{
		if (index >= static_cast<int>(tagsInOrder.size()))
		{
			Log(LogLevel::Warning) << "Great power did not match an existing country!";
			continue;
		}

		const auto& tag = tagsInOrder.at(index);
		world->greatPowers.push_back(tag);
	}
}


void Vic2::World::Factory::setProvinceOwners()
{
	Log(LogLevel::Info) << "\tAssigning province owners";
	for (auto& [provinceNum, province]: world->provinces)
	{
		if (province->getOwner().empty())
		{
			continue;
		}

		if (auto country = world->countries.find(province->getOwner()); country != world->countries.end())
		{
			country->second.addProvince(provinceNum, province);
		}
		else
		{
			Log(LogLevel::Warning) << "Trying to assign province " << provinceNum << " to " << province->getOwner()
										  << ", but country does not exist.";
		}
	}
	for (auto& [unused, country]: world->countries)
	{
		country.putProvincesInStates();
		country.handleMissingCulture(*theCultureGroups);
	}
}


void Vic2::World::Factory::addProvinceCoreInfoToCountries()
{
	Log(LogLevel::Info) << "\tAssigning cores to countries";
	for (const auto& [unused, province]: world->provinces)
	{
		auto provinceCores = province->getCores();
		for (const auto& coreCountryString: provinceCores)
		{
			auto coreCountry = world->countries.find(coreCountryString);
			if (coreCountry != world->countries.end())
			{
				coreCountry->second.addCore(province);
			}
		}
	}
}


void Vic2::World::Factory::removeSimpleLandlessNations()
{
	Log(LogLevel::Info) << "\tRemoving simple landless nations";
	for (auto& [tag, country]: world->countries)
	{
		if (country.hasLand())
		{
			continue;
		}

		std::vector<std::shared_ptr<Province>> coresToKeep;
		for (auto& core: country.getCores())
		{
			if (shouldCoreBeRemoved(*core, country))
			{
				core->removeCore(tag);
			}
			else
			{
				coresToKeep.push_back(core);
			}
		}
		country.replaceCores(coresToKeep);

		if (!country.hasCoreOnCapital())
		{
			country.replaceCores({});
		}
	}
}


constexpr double ACCEPTED_CULTURE_THRESHOLD = 0.25;
bool Vic2::World::Factory::shouldCoreBeRemoved(const Province& core, const Country& country) const
{
	if (core.getOwner().empty())
	{
		return true; // test this
	}

	const auto owner = world->countries.find(core.getOwner());
	if (owner == world->countries.end())
	{
		return true;
	}
	if (country.getPrimaryCulture() == owner->second.getPrimaryCulture())
	{
		return true;
	}
	if (owner->second.isAnAcceptedCulture(country.getPrimaryCulture()))
	{
		return true;
	}
	if (core.getPercentageWithCultures(country.getAcceptedCultures()) < ACCEPTED_CULTURE_THRESHOLD)
	{
		return true;
	}

	return false;
}


void Vic2::World::Factory::determineEmployedWorkers()
{
	Log(LogLevel::Info) << "\tFinding employed workers";
	for (auto& [unused, country]: world->countries)
	{
		country.determineEmployedWorkers();
	}
}


void Vic2::World::Factory::removeEmptyNations()
{
	Log(LogLevel::Info) << "\tRemoving empty nations";
	for (auto country = world->countries.begin(); country != world->countries.end();)
	{
		if (country->second.isEmpty())
		{
			country = world->countries.erase(country);
		}
		else
		{
			++country;
		}
	}
}


void Vic2::World::Factory::addWarsToCountries(const std::vector<War>& wars)
{
	Log(LogLevel::Info) << "\tReconstructing wars";
	for (const auto& war: wars)
	{
		auto warStarter = world->countries.find(war.getOriginalAttacker());
		if (warStarter == world->countries.end())
		{
			continue;
		}
		warStarter->second.addWar(war);

		for (const auto& participant: war.getAttackers())
		{
			auto participantCountry = world->countries.find(participant);
			if (participantCountry == world->countries.end())
			{
				continue;
			}
			participantCountry->second.setAtWar();
		}

		for (const auto& participant: war.getDefenders())
		{
			auto participantCountry = world->countries.find(participant);
			if (participantCountry == world->countries.end())
			{
				continue;
			}
			participantCountry->second.setAtWar();
		}
	}
}


void Vic2::World::Factory::overallMergeNations(bool debug)
{
	Log(LogLevel::Info) << "\tMerging nations";
	const auto theMergeRules = Mappers::MergeRules::Factory().importMergeRules();
	for (const auto& [master, slaves]: theMergeRules->getRules())
	{
		mergeNations(master, slaves, debug);
	}
}


void Vic2::World::Factory::mergeNations(const std::string& masterTag,
	 const std::vector<std::string>& slaveTags,
	 bool debug)
{
	if (auto master = world->countries.find(masterTag); master != world->countries.end())
	{
		for (const auto& slaveTag: slaveTags)
		{
			if (const auto& slave = world->countries.find(slaveTag); slave != world->countries.end())
			{
				master->second.eatCountry(slave->second, debug);
			}
			world->countries.erase(slaveTag);
		}
		master->second.mergeStates(*world->theStateDefinitions);
	}
}


void Vic2::World::Factory::setLocalisations(Localisations& vic2Localisations)
{
	Log(LogLevel::Info) << "\tSetting localisations";
	for (auto& [unused, country]: world->countries)
	{
		country.setLocalisationNames(vic2Localisations);
		country.setLocalisationAdjectives(vic2Localisations);
	}
}


void Vic2::World::Factory::checkAllProvincesMapped(const Mappers::ProvinceMapper& provinceMapper) const
{
	Log(LogLevel::Info) << "\tChecking all provinces are mapped";
	for (const auto& [provinceNum, unused]: world->provinces)
	{
		if (!provinceMapper.isVic2ProvinceMapped(provinceNum))
		{
			Log(LogLevel::Warning) << "No mapping for Vic2 province " << provinceNum;
		}
	}
}


void Vic2::World::Factory::consolidateConquerStrategies()
{
	for (auto& [unused, country]: world->countries)
	{
		country.consolidateConquerStrategies(world->provinces);
	}
}


// Move armies to their owner's capital (by setting location to nullopt) if they are in another nation's territory and
// said nation isn't at war with the owner.
void Vic2::World::Factory::moveArmiesHome()
{
	for (auto& [tag, country]: world->countries)
	{
		for (auto& army: country.getModifiableArmies())
		{
			// if the army doesn't have a location, there's nothing to do
			auto possibleLocation = army.getLocation();
			if (!possibleLocation)
			{
				continue;
			}

			// if the province number isn't an imported province, just continue
			const auto& possibleProvince = world->provinces.find(*possibleLocation);
			if (possibleProvince == world->provinces.end())
			{
				continue;
			}

			// if there is no province owner (such as sea provinces), the location is fine
			const auto provinceOwner = possibleProvince->second->getOwner();
			if (provinceOwner.empty())
			{
				continue;
			}

			// if in home territory the location is fine
			if (provinceOwner == tag)
			{
				continue;
			}

			// if the countries are at war with another, the armies can be there
			auto atWarWithAnother = false;
			if (country.isAtWar())
			{
				for (const auto& war: wars)
				{
					if ((war.getAttackers().contains(tag) && war.getDefenders().contains(provinceOwner)) ||
						 (war.getAttackers().contains(provinceOwner) && war.getDefenders().contains(tag)))
					{
						atWarWithAnother = true;
					}
				}
			}
			if (atWarWithAnother)
			{
				continue;
			}

			// enough, send the country to its owner's capital
			army.setLocation(std::nullopt);
		}
	}
}


// Vic2 battles when opposing armies are in the same province. This is unlike HoI4 battles and actually causes an HoI4
// crash.
//	For all cases where armies from different countries are in the same province, move any armies not belonging to the
// provinces owner to an undefined location. This will be handled properly when constructing HoI4 divisions, attempting
// to move them to the owner's capital.
void Vic2::World::Factory::removeBattles()
{
	const auto armyLocations = determineArmyLocations();

	for (auto& [location, armies]: armyLocations)
	{
		if (armies.size() == 1)
		{
			continue;
		}
		if (!world->provinces.contains(location)) // true of sea provinces
		{
			continue;
		}
		if (!armiesHaveDifferentOwners(armies))
		{
			continue;
		}

		const auto& provinceOwner = world->provinces.at(location)->getOwner();
		for (const auto& army: armies)
		{
			if (army->getOwner() != provinceOwner)
			{
				army->setLocation(std::nullopt);
			}
		}
	}
}


std::map<int, std::vector<Vic2::Army*>> Vic2::World::Factory::determineArmyLocations() const
{
	std::map<int, std::vector<Army*>> armyLocations;

	for (auto& [tag, country]: world->countries)
	{
		for (auto& army: country.getModifiableArmies())
		{
			auto possibleLocation = army.getLocation();
			if (possibleLocation)
			{
				auto [iterator, inserted] =
					 armyLocations.insert(std::make_pair(*possibleLocation, std::vector<Army*>{&army}));
				if (!inserted)
				{
					iterator->second.push_back(&army);
				}
			}
		}
	}

	return armyLocations;
}


bool Vic2::World::Factory::armiesHaveDifferentOwners(const std::vector<Army*>& armies)
{
	auto armiesFromDifferentOwners = false;
	const auto& firstOwner = (*armies.begin())->getOwner();
	for (const auto& army: armies)
	{
		if (army->getOwner() != firstOwner)
		{
			armiesFromDifferentOwners = true;
			break;
		}
	}

	return armiesFromDifferentOwners;
}