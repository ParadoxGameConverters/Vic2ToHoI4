#include "HoI4States.h"
#include "Configuration.h"
#include "DefaultState.h"
#include "HOI4World/HoI4Country.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/Localisations/GrammarMappings.h"
#include "HOI4World/Map/CoastalProvinces.h"
#include "HOI4World/Map/HoI4Provinces.h"
#include "HOI4World/Map/ImpassableProvinces.h"
#include "HOI4World/Map/Resources.h"
#include "HOI4World/ProvinceDefinitions.h"
#include "HoI4State.h"
#include "Log.h"
#include "Mappers/Country/CountryMapper.h"
#include "OSCompatibilityLayer.h"
#include "StateCategories.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Provinces/Province.h"
#include "V2World/States/State.h"
#include "V2World/States/StateDefinitions.h"
#include "V2World/States/StateFactory.h"
#include "V2World/World/World.h"
#include <queue>
#include <ranges>
#include <unordered_map>



constexpr int NUM_FACTORIES_PER_AIRBASE = 4;
constexpr int AIRBASES_FOR_INFRASTRUCTURE_LEVEL = 6;



HoI4::States::States(const Vic2::World& sourceWorld,
	 const Mappers::CountryMapper& countryMap,
	 const std::map<int, Province>& theProvinces,
	 const CoastalProvinces& theCoastalProvinces,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const StrategicRegions& strategicRegions,
	 const Vic2::Localisations& vic2Localisations,
	 const ProvinceDefinitions& provinceDefinitions,
	 const MapData& mapData,
	 Localisation& hoi4Localisations,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	int num;

	Log(LogLevel::Info) << "\tConverting states";
	registerKeyword("state", [this, &num](std::istream& theStream) {
		defaultStates.insert(std::make_pair(num, DefaultState(theStream)));
	});

	for (const auto& stateFile: commonItems::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/history/states"))
	{
		num = stoi(stateFile.substr(0, stateFile.find_first_of('-')));
		parseFile(theConfiguration.getHoI4Path() + "/history/states/" + stateFile);
	}

	const ImpassableProvinces theImpassableProvinces(defaultStates);

	determineOwnersAndCores(countryMap, sourceWorld, provinceDefinitions, provinceMapper);
	createStates(sourceWorld.getCountries(),
		 sourceWorld.getProvinces(),
		 theProvinces,
		 theImpassableProvinces,
		 countryMap,
		 theCoastalProvinces,
		 theStateDefinitions,
		 strategicRegions,
		 vic2Localisations,
		 hoi4Localisations,
		 provinceMapper,
		 mapData,
		 theConfiguration);

	languageCategories.emplace("msnc", std::set<int>{});
	languageCategories.emplace("msac", std::set<int>{});
	languageCategories.emplace("msav", std::set<int>{});
	languageCategories.emplace("msnv", std::set<int>{});
	languageCategories.emplace("mpac", std::set<int>{});
	languageCategories.emplace("mpav", std::set<int>{});
	languageCategories.emplace("mpnc", std::set<int>{});
	languageCategories.emplace("mpnv", std::set<int>{});
	languageCategories.emplace("fsnc", std::set<int>{});
	languageCategories.emplace("fsac", std::set<int>{});
	languageCategories.emplace("fsav", std::set<int>{});
	languageCategories.emplace("fsnv", std::set<int>{});
	languageCategories.emplace("fpac", std::set<int>{});
	languageCategories.emplace("fpav", std::set<int>{});
	languageCategories.emplace("fpnc", std::set<int>{});
	languageCategories.emplace("fpnv", std::set<int>{});
}


void HoI4::States::determineOwnersAndCores(const Mappers::CountryMapper& countryMap,
	 const Vic2::World& sourceWorld,
	 const ProvinceDefinitions& provinceDefinitions,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	for (auto provinceNumber: provinceDefinitions.getLandProvinces())
	{
		auto sourceProvinceNumbers = retrieveSourceProvinceNumbers(provinceNumber, provinceMapper);
		if (sourceProvinceNumbers)
		{
			auto potentialOwners = determinePotentialOwners(*sourceProvinceNumbers, sourceWorld);
			if (potentialOwners.empty())
			{
				ownersMap.insert(std::make_pair(provinceNumber, ""));
				continue;
			}
			auto oldOwner = selectProvinceOwner(potentialOwners);


			auto HoI4Tag = countryMap.getHoI4Tag(oldOwner);
			if (!HoI4Tag)
			{
				Log(LogLevel::Warning) << "Could not map states owned by " << oldOwner
											  << " in Vic2, as there is no matching HoI4 country.";
				continue;
			}
			ownersMap.insert(make_pair(provinceNumber, *HoI4Tag));

			auto cores = determineCores(*sourceProvinceNumbers, oldOwner, countryMap, *HoI4Tag, sourceWorld);
			coresMap.insert(make_pair(provinceNumber, cores));
		}
	}
}


std::optional<std::vector<int>> HoI4::States::retrieveSourceProvinceNumbers(int provNum,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	auto provinceLink = provinceMapper.getHoI4ToVic2ProvinceMapping(provNum);
	if (provinceLink.empty())
	{
		return std::nullopt;
	}

	return provinceLink;
}


std::map<std::string, std::pair<int, int>> HoI4::States::determinePotentialOwners(
	 const std::vector<int>& sourceProvinceNumbers,
	 const Vic2::World& sourceWorld)
{
	std::map<std::string, std::pair<int, int>> potentialOwners;

	for (auto srcProvNum: sourceProvinceNumbers)
	{
		auto srcProvince = sourceWorld.getProvince(srcProvNum);
		if (!srcProvince)
		{
			Log(LogLevel::Warning) << "Old province " << srcProvNum << " does not exist (bad mapping?)";
			continue;
		}
		auto owner = (*srcProvince)->getOwner();
		if (owner.empty())
		{
			continue;
		}

		if (!potentialOwners.contains(owner))
		{
			potentialOwners[owner] = std::make_pair(0, 0);
		}
		potentialOwners[owner].first++;
		potentialOwners[owner].second += (*srcProvince)->getTotalPopulation();
	}

	return potentialOwners;
}


std::string HoI4::States::selectProvinceOwner(const std::map<std::string, std::pair<int, int>>& potentialOwners)
{
	std::string oldOwner;
	std::pair<int, int> oldOwnerStats;
	for (const auto& potentialOwner: potentialOwners)
	{
		// I am the new owner if there is no current owner
		if (oldOwner.empty())
		{
			oldOwner = potentialOwner.first;
			oldOwnerStats = potentialOwner.second;
		}

		// I am the new owner if I have more provinces than the current owner,
		// or I have the same number of provinces but more population than the current owner
		if ((potentialOwner.second.first > oldOwnerStats.first) ||
			 ((potentialOwner.second.first == oldOwnerStats.first) &&
				  (potentialOwner.second.second > oldOwnerStats.second)))
		{
			oldOwner = potentialOwner.first;
			oldOwnerStats = potentialOwner.second;
		}
	}

	return oldOwner;
}


std::set<std::pair<std::string, std::string>> HoI4::States::determineCores(const std::vector<int>& sourceProvinces,
	 const std::string& Vic2Owner,
	 const Mappers::CountryMapper& countryMap,
	 const std::string& newOwner,
	 const Vic2::World& sourceWorld)
{
	std::set<std::pair<std::string, std::string>> cores;

	for (auto sourceProvinceNum: sourceProvinces)
	{
		auto sourceProvince = sourceWorld.getProvince(sourceProvinceNum);
		if (!sourceProvince)
		{
			continue;
		}

		for (const auto& Vic2Core: (*sourceProvince)->getCores())
		{
			auto HoI4CoreTag = countryMap.getHoI4Tag(Vic2Core);
			if (HoI4CoreTag)
			{
				// skip this core if the country is the owner of the V2 province but not the HoI4 province
				// (i.e. "avoid boundary conflicts that didn't exist in V2").
				// this country may still get core via a province that DID belong to the current HoI4 owner
				if ((Vic2Core == Vic2Owner) && (*HoI4CoreTag != newOwner))
				{
					continue;
				}

				cores.insert(std::make_pair(Vic2Core, *HoI4CoreTag));
			}
		}
	}

	return cores;
}


void HoI4::States::createStates(const std::map<std::string, Vic2::Country>& sourceCountries,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& sourceProvinces,
	 const std::map<int, Province>& theProvinces,
	 const ImpassableProvinces& theImpassableProvinces,
	 const Mappers::CountryMapper& countryMap,
	 const CoastalProvinces& theCoastalProvinces,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const StrategicRegions& strategicRegions,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const MapData& mapData,
	 const Configuration& theConfiguration)
{
	const auto grammarMappings = GrammarMappings().importGrammarMappings();

	std::set<int> ownedProvinces;

	for (const auto& country: sourceCountries)
	{
		for (const auto& vic2State: country.second.getStates())
		{
			auto possibleHoI4Owner = countryMap.getHoI4Tag(country.first);
			if (possibleHoI4Owner)
			{
				createMatchingHoI4State(vic2State,
					 *possibleHoI4Owner,
					 theImpassableProvinces,
					 countryMap,
					 sourceCountries,
					 theCoastalProvinces,
					 theStateDefinitions,
					 strategicRegions,
					 vic2Localisations,
					 hoi4Localisations,
					 provinceMapper,
					 mapData,
					 theProvinces,
					 sourceProvinces,
					 theConfiguration,
					 grammarMappings);
				for (const auto& province: vic2State.getProvinceNumbers())
				{
					ownedProvinces.insert(province);
				}
			}
		}
	}

	std::map<int, std::shared_ptr<Vic2::Province>> unownedProvinces;
	for (const auto& vic2Province: sourceProvinces)
	{
		if (!ownedProvinces.contains(vic2Province.first))
		{
			unownedProvinces.insert(vic2Province);
		}
	}

	Vic2::State::Factory factory;
	while (!unownedProvinces.empty())
	{
		std::unordered_map<int, std::shared_ptr<Vic2::Province>> stateProvinces;

		auto stateProvinceNumbers = theStateDefinitions.getAllProvinces(unownedProvinces.begin()->first);
		if (stateProvinceNumbers.empty())
		{
			unownedProvinces.erase(unownedProvinces.begin());
			continue;
		}
		for (auto provinceNum: stateProvinceNumbers)
		{
			auto province = unownedProvinces.find(provinceNum);
			if (province != unownedProvinces.end())
			{
				stateProvinces.insert(*province);
				unownedProvinces.erase(province);
			}
		}
		const auto newState = factory.getUnownedState(stateProvinces, theStateDefinitions);
		createMatchingHoI4State(*newState,
			 "",
			 theImpassableProvinces,
			 countryMap,
			 sourceCountries,
			 theCoastalProvinces,
			 theStateDefinitions,
			 strategicRegions,
			 vic2Localisations,
			 hoi4Localisations,
			 provinceMapper,
			 mapData,
			 theProvinces,
			 sourceProvinces,
			 theConfiguration,
			 grammarMappings);
	}

	const auto manpower = getTotalManpower();
	Log(LogLevel::Info) << "\t\tTotal manpower was " << manpower << ", which is " << manpower / 20438756.2
							  << "% of default HoI4.";
}


void HoI4::States::createMatchingHoI4State(const Vic2::State& vic2State,
	 const std::string& stateOwner,
	 const ImpassableProvinces& theImpassableProvinces,
	 const Mappers::CountryMapper& countryMapper,
	 const std::map<std::string, Vic2::Country>& sourceCountries,
	 const CoastalProvinces& theCoastalProvinces,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const StrategicRegions& strategicRegions,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const MapData& mapData,
	 const std::map<int, Province>& provinces,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2Provinces,
	 const Configuration& theConfiguration,
	 const std::map<std::string, std::string>& grammarMappings)
{
	const auto allProvinces = getProvincesInState(vic2State, stateOwner, provinceMapper);
	const auto initialConnectedProvinceSets = getConnectedProvinceSets(allProvinces, mapData, provinces);
	auto finalConnectedProvinceSets =
		 consolidateProvinceSets(initialConnectedProvinceSets, strategicRegions.getProvinceToStrategicRegionMap());

	for (const auto& connectedProvinces: finalConnectedProvinceSets)
	{
		std::set<int> passableProvinces;
		std::set<int> impassableProvinces;
		for (auto province: connectedProvinces)
		{
			if (theImpassableProvinces.isProvinceImpassable(province))
			{
				impassableProvinces.insert(province);
			}
			else
			{
				passableProvinces.insert(province);
			}
		}

		if (!passableProvinces.empty())
		{
			auto [existing, emplaced] = languageCategories.emplace(vic2State.getLanguageCategory(), std::set{nextStateID});
			if (!emplaced)
			{
				existing->second.insert(nextStateID);
			}
			State newState(vic2State, nextStateID, stateOwner);
			if (!impassableProvinces.empty())
			{
				newState.markHadImpassablePart();
			}
			addProvincesAndCoresToNewState(newState, sourceCountries, passableProvinces, provinceMapper, vic2Provinces);
			newState.convertControlledProvinces(vic2State.getForeignControlledProvinces(), provinceMapper, countryMapper);
			newState.tryToCreateVP(vic2State, provinceMapper, theConfiguration);
			newState.addManpower(vic2State.getProvinces(), provinceMapper, theConfiguration);
			newState.convertNavalBases(vic2State.getNavalBases(), theCoastalProvinces, provinceMapper);
			states.insert(std::make_pair(nextStateID, newState));
			nextStateID++;
			hoi4Localisations.addStateLocalisation(newState,
				 vic2State,
				 theStateDefinitions,
				 vic2Localisations,
				 provinceMapper,
				 grammarMappings);
		}

		if (!impassableProvinces.empty())
		{
			auto [existing, emplaced] = languageCategories.emplace(vic2State.getLanguageCategory(), std::set{nextStateID});
			if (!emplaced)
			{
				existing->second.insert(nextStateID);
			}
			State newState(vic2State, nextStateID, stateOwner);
			addProvincesAndCoresToNewState(newState, sourceCountries, impassableProvinces, provinceMapper, vic2Provinces);
			newState.makeImpassable();
			newState.tryToCreateVP(vic2State, provinceMapper, theConfiguration);
			newState.addManpower(vic2State.getProvinces(), provinceMapper, theConfiguration);
			newState.convertNavalBases(vic2State.getNavalBases(), theCoastalProvinces, provinceMapper);
			states.insert(std::make_pair(nextStateID, newState));
			nextStateID++;
			hoi4Localisations.addStateLocalisation(newState,
				 vic2State,
				 theStateDefinitions,
				 vic2Localisations,
				 provinceMapper,
				 grammarMappings);
		}
	}
}


std::set<int> HoI4::States::getProvincesInState(const Vic2::State& vic2State,
	 const std::string& owner,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	std::set<int> provinces;
	for (auto vic2ProvinceNum: vic2State.getProvinceNumbers())
	{
		for (auto HoI4ProvNum: provinceMapper.getVic2ToHoI4ProvinceMapping(vic2ProvinceNum))
		{
			if (isProvinceOwnedByCountry(HoI4ProvNum, owner) && isProvinceNotAlreadyAssigned(HoI4ProvNum))

			{
				provinces.insert(HoI4ProvNum);
				assignedProvinces.insert(HoI4ProvNum);
			}
		}
	}

	return provinces;
}


std::vector<std::set<int>> HoI4::States::getConnectedProvinceSets(std::set<int> provinceNumbers,
	 const MapData& mapData,
	 const std::map<int, Province>& provinces)
{
	std::vector<std::set<int>> connectedProvinceSets;
	while (!provinceNumbers.empty())
	{
		std::set<int> connectedProvinceSet;

		std::queue<int> openProvinces;
		openProvinces.push(*provinceNumbers.begin());
		std::set<int> closedProvinces{*provinceNumbers.begin()};
		while (!openProvinces.empty() && !provinceNumbers.empty())
		{
			auto currentProvince = openProvinces.front();
			openProvinces.pop();
			if (provinceNumbers.contains(currentProvince))
			{
				connectedProvinceSet.insert(currentProvince);
				provinceNumbers.erase(currentProvince);
			}

			for (const auto& neighbor: mapData.getNeighbors(currentProvince))
			{
				if (!closedProvinces.contains(neighbor))
				{
					if (auto province = provinces.find(neighbor); province != provinces.end())
					{
						if (province->second.isLandProvince())
						{
							openProvinces.push(neighbor);
							closedProvinces.insert(neighbor);
						}
					}
				}
			}
		}

		connectedProvinceSets.push_back(connectedProvinceSet);
	}

	return connectedProvinceSets;
}


std::vector<std::set<int>> HoI4::States::consolidateProvinceSets(std::vector<std::set<int>> connectedProvinceSets,
	 const std::map<int, int>& provinceToStrategicRegionMap)
{
	std::vector<std::set<int>> newConnectedProvinceSets;
	while (!connectedProvinceSets.empty())
	{
		auto baseSet = connectedProvinceSets.front();
		connectedProvinceSets.erase(connectedProvinceSets.begin());

		std::optional<int> strategicRegion;
		if (const auto& mapping = provinceToStrategicRegionMap.find(*baseSet.begin());
			 mapping != provinceToStrategicRegionMap.end())
		{
			strategicRegion = mapping->second;
		}

		for (auto currentSet = connectedProvinceSets.begin(); currentSet != connectedProvinceSets.end();)
		{
			if (const auto& mapping = provinceToStrategicRegionMap.find(*currentSet->begin());
				 mapping != provinceToStrategicRegionMap.end() && strategicRegion && *strategicRegion == mapping->second)
			{
				baseSet.insert(currentSet->begin(), currentSet->end());
				currentSet = connectedProvinceSets.erase(currentSet);
				continue;
			}
			++currentSet;
		}

		newConnectedProvinceSets.push_back(baseSet);
	}

	return newConnectedProvinceSets;
}


void HoI4::States::addProvincesAndCoresToNewState(State& newState,
	 const std::map<std::string, Vic2::Country>& sourceCountries,
	 const std::set<int>& provinceNumbers,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2Provinces)
{
	std::set<std::pair<std::string, std::string>> possibleCores;
	for (auto province: provinceNumbers)
	{
		newState.addProvince(province);
		provinceToStateIDMap.insert(std::make_pair(province, newState.getID()));
		if (auto coresMapping = coresMap.find(province); coresMapping != coresMap.end())
		{
			possibleCores.insert(coresMapping->second.begin(), coresMapping->second.end());
		}
	}

	std::set<int> sourceProvinceNums;
	for (const auto& province: provinceNumbers)
	{
		const auto possibleProvinces = provinceMapper.getHoI4ToVic2ProvinceMapping(province);
		sourceProvinceNums.insert(possibleProvinces.begin(), possibleProvinces.end());
	}

	for (const auto& [Vic2Core, HoI4Core]: possibleCores)
	{
		const auto sourceCountry = sourceCountries.find(Vic2Core);
		if (sourceCountry == sourceCountries.end())
		{
			continue;
		}
		auto acceptedCultures = sourceCountry->second.getAcceptedCultures();
		acceptedCultures.insert(sourceCountry->second.getPrimaryCulture());

		uint64_t totalPopulation = 0;
		double acceptedPopulation = 0;
		for (const auto& sourceProvinceNum: sourceProvinceNums)
		{
			if (const auto& vic2Province = vic2Provinces.find(sourceProvinceNum); vic2Province != vic2Provinces.end())
			{
				const auto provincePopulation = vic2Province->second->getTotalPopulation();
				totalPopulation += provincePopulation;
				acceptedPopulation +=
					 provincePopulation * vic2Province->second->getPercentageWithCultures(acceptedCultures);
			}
		}

		if (acceptedPopulation / static_cast<double>(totalPopulation) >= 0.5)
		{
			newState.addCores({HoI4Core});
		}
		else
		{
			newState.addClaims({HoI4Core});
		}
	}
}


bool HoI4::States::isProvinceOwnedByCountry(int provNum, const std::string& stateOwner) const
{
	const auto provinceOwnerItr = ownersMap.find(provNum);
	return (provinceOwnerItr != ownersMap.end()) && (provinceOwnerItr->second == stateOwner);
}


bool HoI4::States::isProvinceNotAlreadyAssigned(int provNum) const
{
	return !assignedProvinces.contains(provNum);
}


unsigned int HoI4::States::getTotalManpower() const
{
	unsigned int totalManpower = 0;
	for (const auto& state: states)
	{
		totalManpower += state.second.getManpower();
	}

	return totalManpower;
}


void HoI4::States::convertAirBases(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::vector<std::shared_ptr<Country>>& greatPowers)
{
	Log(LogLevel::Info) << "\tConverting air bases";
	addBasicAirBases();
	addCapitalAirBases(countries);
	addGreatPowerAirBases(greatPowers);
}


void HoI4::States::addCapitalAirBases(const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	for (const auto& country: countries)
	{
		if (auto capitalState = states.find(*country.second->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.addAirBase(5);
		}
	}
}


void HoI4::States::addGreatPowerAirBases(const std::vector<std::shared_ptr<Country>>& greatPowers)
{
	for (const auto& greatPower: greatPowers)
	{
		if (auto capitalState = states.find(*greatPower->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.addAirBase(5);
		}
	}
}


void HoI4::States::addBasicAirBases()
{
	for (auto& state: states)
	{
		const auto numAirbases =
			 (state.second.getCivFactories() + state.second.getMilFactories()) / NUM_FACTORIES_PER_AIRBASE;
		state.second.addAirBase(numAirbases);

		if (state.second.getInfrastructure() >= AIRBASES_FOR_INFRASTRUCTURE_LEVEL)
		{
			state.second.addAirBase(1);
		}
	}
}


void HoI4::States::convertResources()
{
	Log(LogLevel::Info) << "\tConverting resources";
	const Resources resourceMap;

	for (auto& state: states)
	{
		for (auto provinceNumber: state.second.getProvinces())
		{
			for (const auto& resource: resourceMap.getResourcesInProvince(provinceNumber))
			{
				state.second.addResource(resource.first, resource.second);
			}
		}
	}
}


void HoI4::States::putIndustryInStates(const std::map<std::string, double>& factoryWorkerRatios,
	 const CoastalProvinces& theCoastalProvinces,
	 const Configuration& theConfiguration)
{
	const StateCategories theStateCategories(theConfiguration);

	for (auto& HoI4State: states)
	{
		auto ratioMapping = factoryWorkerRatios.find(HoI4State.second.getOwner());
		if (ratioMapping == factoryWorkerRatios.end())
		{
			continue;
		}

		HoI4State.second.convertIndustry(ratioMapping->second, theStateCategories, theCoastalProvinces);
	}
}


void HoI4::States::convertCapitalVPs(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::vector<std::shared_ptr<Country>>& greatPowers)
{
	Log(LogLevel::Info) << "\tConverting capital VPs";

	addCapitalVictoryPoints(countries);
	addGreatPowerVPs(greatPowers);
}


void HoI4::States::addCapitalsToStates(const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	Log(LogLevel::Info) << "\tAdding capitals to states";
	for (const auto& country: countries)
	{
		if (auto capitalState = states.find(*country.second->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.setAsCapitalState();
			if (auto capitalProvince = country.second->getCapitalProvince(); capitalProvince)
			{
				capitalState->second.setVPLocation(*capitalProvince);
			}
		}
	}
}


void HoI4::States::giveProvinceControlToCountry(int provinceNum,
	 const std::string& country,
	 const std::set<std::string>& ownersToSkip)
{
	const auto& stateIdMapping = provinceToStateIDMap.find(provinceNum);
	if (stateIdMapping == provinceToStateIDMap.end())
	{
		return;
	}
	const auto HoI4StateId = stateIdMapping->second;

	const auto stateItr = states.find(HoI4StateId);
	if (stateItr == states.end())
	{
		return;
	}
	auto& state = stateItr->second;

	state.removeControlledProvince(provinceNum);
	if (ownersToSkip.contains(state.getOwner()))
	{
		return;
	}
	state.setControlledProvince(provinceNum, country);
}


void HoI4::States::addCoresToCorelessStates(const std::map<std::string, Vic2::Country>& sourceCountries,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2Provinces,
	 bool debug)
{
	for (auto& [id, state]: states)
	{
		if (!state.getCores().empty())
		{
			continue;
		}

		std::set<std::pair<std::string, std::string>> possibleCores;
		std::set<int> sourceProvinceNums;
		for (auto province: state.getProvinces())
		{
			if (auto coresMapping = coresMap.find(province); coresMapping != coresMap.end())
			{
				possibleCores.insert(coresMapping->second.begin(), coresMapping->second.end());
			}

			const auto possibleProvinces = provinceMapper.getHoI4ToVic2ProvinceMapping(province);
			sourceProvinceNums.insert(possibleProvinces.begin(), possibleProvinces.end());
		}

		std::vector<std::pair<std::string, double>> acceptedPopulations;
		for (const auto& [Vic2Core, HoI4Core]: possibleCores)
		{
			const auto sourceCountry = sourceCountries.find(Vic2Core);
			if (sourceCountry == sourceCountries.end())
			{
				continue;
			}
			auto acceptedCultures = sourceCountry->second.getAcceptedCultures();
			acceptedCultures.insert(sourceCountry->second.getPrimaryCulture());

			double acceptedPopulation = 0;
			for (const auto& sourceProvinceNum: sourceProvinceNums)
			{
				if (const auto& vic2Province = vic2Provinces.find(sourceProvinceNum); vic2Province != vic2Provinces.end())
				{
					const auto provincePopulation = vic2Province->second->getTotalPopulation();
					acceptedPopulation +=
						 provincePopulation * vic2Province->second->getPercentageWithCultures(acceptedCultures);
				}
			}
			acceptedPopulations.push_back(std::make_pair(HoI4Core, acceptedPopulation));
		}

		if (!acceptedPopulations.empty())
		{
			std::ranges::sort(acceptedPopulations,
				 [](const std::pair<std::string, double>& lhs, const std::pair<std::string, double>& rhs) {
					 return lhs < rhs;
				 });
			state.addCores({acceptedPopulations[0].first});
		}

		if (state.getCores().empty())
		{
			if (debug)
			{
				Log(LogLevel::Debug) << "State #" << id << " has no cores";
			}
		}
	}
}


void HoI4::States::addGreatPowerVPs(const std::vector<std::shared_ptr<Country>>& greatPowers)
{
	int ranking = 1;
	for (const auto& greatPower: greatPowers)
	{
		if (auto capitalState = states.find(*greatPower->getCapitalState()); capitalState != states.end())
		{
			if (ranking < 5)
			{
				capitalState->second.setVPValue(50);
			}
			else
			{
				capitalState->second.setVPValue(40);
			}
		}
		++ranking;
	}
}


void HoI4::States::addCapitalVictoryPoints(const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	std::vector<std::string> tags;
	for (const auto& [tag, country]: countries)
	{
		if (!country->isGreatPower())
		{
			tags.push_back(tag);
		}
	}
	std::sort(tags.begin(), tags.end(), [countries](const std::string& a, const std::string& b) {
		return countries.at(a)->getStrengthOverTime(1.0) > countries.at(b)->getStrengthOverTime(1.0);
	});

	auto i = 0;
	for (; i < 4 && i < tags.size(); i++)
	{
		auto country = countries.at(tags[i]);
		if (auto capitalState = states.find(*country->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.setVPValue(30);
		}
	}
	for (; i < 8 && i < tags.size(); i++)
	{
		auto country = countries.at(tags[i]);
		if (auto capitalState = states.find(*country->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.setVPValue(25);
		}
	}
	for (; i < 16 && i < tags.size(); i++)
	{
		auto country = countries.at(tags[i]);
		if (auto capitalState = states.find(*country->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.setVPValue(20);
		}
	}
	for (; i < tags.size() / 2; i++)
	{
		auto country = countries.at(tags[i]);
		if (auto capitalState = states.find(*country->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.setVPValue(15);
		}
	}
	for (; i < tags.size(); i++)
	{
		auto country = countries.at(tags[i]);
		if (auto capitalState = states.find(*country->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.setVPValue(10);
		}
	}
}