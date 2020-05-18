#include "HoI4States.h"
#include "../../Configuration.h"
#include "../../HOI4World/ProvinceDefinitions.h"
#include "../../Mappers/CountryMapping.h"
#include "../../V2World/Country.h"
#include "../../V2World/Province.h"
#include "../../V2World/State.h"
#include "../../V2World/StateDefinitions.h"
#include "../../V2World/Vic2Localisations.h"
#include "../../V2World/World.h"
#include "../HoI4Country.h"
#include "../HoI4Localisation.h"
#include "../Map/CoastalProvinces.h"
#include "../Map/HoI4Provinces.h"
#include "../Map/ImpassableProvinces.h"
#include "../Map/Resources.h"
#include "DefaultState.h"
#include "HoI4State.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "StateCategories.h"
#include <queue>



constexpr int NUM_FACTORIES_PER_AIRBASE = 4;
constexpr int AIRBASES_FOR_INFRASTRUCTURE_LEVEL = 6;



HoI4::States::States(const Vic2::World* sourceWorld,
	 const CountryMapper& countryMap,
	 const std::map<int, Province>& theProvinces,
	 const CoastalProvinces& theCoastalProvinces,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const StrategicRegions& strategicRegions,
	 const Vic2::Localisations& vic2Localisations,
	 const ProvinceDefinitions& provinceDefinitions,
	 const MapData& mapData,
	 Localisation& hoi4Localisations,
	 const mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	int num;

	Log(LogLevel::Info) << "\tConverting states";
	registerKeyword(std::regex("state"), [this, &num](const std::string& unused, std::istream& theStream) {
		defaultStates.insert(std::make_pair(num, DefaultState(theStream)));
	});

	std::set<std::string> statesFiles;
	Utils::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/history/states", statesFiles);
	for (const auto& stateFile: statesFiles)
	{
		num = stoi(stateFile.substr(0, stateFile.find_first_of('-')));
		parseFile(theConfiguration.getHoI4Path() + "/history/states/" + stateFile);
	}

	const ImpassableProvinces theImpassableProvinces(defaultStates);

	determineOwnersAndCores(countryMap, *sourceWorld, provinceDefinitions, provinceMapper);
	createStates(sourceWorld->getCountries(),
		 sourceWorld->getProvinces(),
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
}


void HoI4::States::determineOwnersAndCores(const CountryMapper& countryMap,
	 const Vic2::World& sourceWorld,
	 const ProvinceDefinitions& provinceDefinitions,
	 const mappers::ProvinceMapper& provinceMapper)
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
	 const mappers::ProvinceMapper& provinceMapper)
{
	if (auto provinceLink = provinceMapper.getHoI4ToVic2ProvinceMapping(provNum); provinceLink && !provinceLink->empty())
	{
		if ((*provinceLink)[0] == 0)
		{
			return std::nullopt;
		}
		return provinceLink;
	}

	Log(LogLevel::Warning) << "No source for HoI4 land province " << provNum;
	return std::nullopt;
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

		if (potentialOwners.find(owner) == potentialOwners.end())
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


std::set<std::string> HoI4::States::determineCores(const std::vector<int>& sourceProvinces,
	 const std::string& Vic2Owner,
	 const CountryMapper& countryMap,
	 const std::string& newOwner,
	 const Vic2::World& sourceWorld)
{
	std::set<std::string> cores;

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

				cores.insert(*HoI4CoreTag);
			}
		}
	}

	return cores;
}


void HoI4::States::createStates(const std::map<std::string, Vic2::Country*>& sourceCountries,
	 const std::map<int, Vic2::Province*>& sourceProvinces,
	 const std::map<int, Province>& theProvinces,
	 const ImpassableProvinces& theImpassableProvinces,
	 const CountryMapper& countryMap,
	 const CoastalProvinces& theCoastalProvinces,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const StrategicRegions& strategicRegions,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 const mappers::ProvinceMapper& provinceMapper,
	 const MapData& mapData,
	 const Configuration& theConfiguration)
{
	std::set<int> ownedProvinces;

	for (const auto& country: sourceCountries)
	{
		for (auto vic2State: country.second->getStates())
		{
			auto possibleHoI4Owner = countryMap.getHoI4Tag(country.first);
			if (possibleHoI4Owner)
			{
				createMatchingHoI4State(vic2State,
					 *possibleHoI4Owner,
					 theImpassableProvinces,
					 countryMap,
					 theCoastalProvinces,
					 theStateDefinitions,
					 strategicRegions,
					 vic2Localisations,
					 hoi4Localisations,
					 provinceMapper,
					 mapData,
					 theProvinces,
					 theConfiguration);
				for (auto province: vic2State->getProvinces())
				{
					ownedProvinces.insert(province->getNumber());
				}
			}
		}
	}

	std::map<int, Vic2::Province*> unownedProvinces;
	for (auto vic2Province: sourceProvinces)
	{
		if (ownedProvinces.count(vic2Province.first) == 0)
		{
			unownedProvinces.insert(vic2Province);
		}
	}

	while (!unownedProvinces.empty())
	{
		std::set<std::pair<int, Vic2::Province*>> stateProvinces;

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

		const auto newState = new Vic2::State(stateProvinces, theStateDefinitions);
		createMatchingHoI4State(newState,
			 "",
			 theImpassableProvinces,
			 countryMap,
			 theCoastalProvinces,
			 theStateDefinitions,
			 strategicRegions,
			 vic2Localisations,
			 hoi4Localisations,
			 provinceMapper,
			 mapData,
			 theProvinces,
			 theConfiguration);
	}

	const auto manpower = getTotalManpower();
	Log(LogLevel::Info) << "\t\tTotal manpower was " << manpower << ", which is " << manpower / 20438756.2
							  << "% of default HoI4.";
}


void HoI4::States::createMatchingHoI4State(const Vic2::State* vic2State,
	 const std::string& stateOwner,
	 const ImpassableProvinces& theImpassableProvinces,
	 const CountryMapper& countryMapper,
	 const CoastalProvinces& theCoastalProvinces,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const StrategicRegions& strategicRegions,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 const mappers::ProvinceMapper& provinceMapper,
	 const MapData& mapData,
	 const std::map<int, Province>& provinces,
	 const Configuration& theConfiguration)
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
			State newState(*vic2State, nextStateID, stateOwner);
			if (!impassableProvinces.empty())
			{
				newState.markHadImpassablePart();
			}
			addProvincesAndCoresToNewState(newState, passableProvinces);
			newState.convertControlledProvinces(vic2State->getProvinces(), provinceMapper, countryMapper);
			newState.tryToCreateVP(*vic2State, provinceMapper, theConfiguration);
			newState.addManpower(vic2State->getProvinces(), provinceMapper, theConfiguration);
			newState.convertNavalBases(vic2State->getProvinces(), theCoastalProvinces, provinceMapper);
			states.insert(std::make_pair(nextStateID, newState));
			nextStateID++;
			hoi4Localisations.addStateLocalisation(newState,
				 *vic2State,
				 theStateDefinitions,
				 vic2Localisations,
				 provinceMapper);
		}

		if (!impassableProvinces.empty())
		{
			State newState(*vic2State, nextStateID, stateOwner);
			addProvincesAndCoresToNewState(newState, impassableProvinces);
			newState.makeImpassable();
			newState.tryToCreateVP(*vic2State, provinceMapper, theConfiguration);
			newState.addManpower(vic2State->getProvinces(), provinceMapper, theConfiguration);
			newState.convertNavalBases(vic2State->getProvinces(), theCoastalProvinces, provinceMapper);
			states.insert(std::make_pair(nextStateID, newState));
			nextStateID++;
			hoi4Localisations.addStateLocalisation(newState,
				 *vic2State,
				 theStateDefinitions,
				 vic2Localisations,
				 provinceMapper);
		}
	}
}


std::set<int> HoI4::States::getProvincesInState(const Vic2::State* vic2State,
	 const std::string& owner,
	 const mappers::ProvinceMapper& provinceMapper)
{
	std::set<int> provinces;
	for (auto vic2ProvinceNum: vic2State->getProvinceNumbers())
	{
		if (auto mapping = provinceMapper.getVic2ToHoI4ProvinceMapping(vic2ProvinceNum))
		{
			for (auto HoI4ProvNum: *mapping)
			{
				if (isProvinceValid(HoI4ProvNum) && isProvinceOwnedByCountry(HoI4ProvNum, owner) &&
					 isProvinceNotAlreadyAssigned(HoI4ProvNum))

				{
					provinces.insert(HoI4ProvNum);
					assignedProvinces.insert(HoI4ProvNum);
				}
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
			if (provinceNumbers.count(currentProvince))
			{
				connectedProvinceSet.insert(currentProvince);
				provinceNumbers.erase(currentProvince);
			}

			for (const auto& neighbor: mapData.getNeighbors(currentProvince))
			{
				if (!closedProvinces.count(neighbor))
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


void HoI4::States::addProvincesAndCoresToNewState(State& newState, const std::set<int>& provinces)
{
	for (auto province: provinces)
	{
		newState.addProvince(province);
		provinceToStateIDMap.insert(std::make_pair(province, newState.getID()));
		if (auto coresMapping = coresMap.find(province); coresMapping != coresMap.end())
		{
			newState.addCores(coresMapping->second);
		}
	}
}


bool HoI4::States::isProvinceValid(int provNum)
{
	return provNum != 0;
}


bool HoI4::States::isProvinceOwnedByCountry(int provNum, const std::string& stateOwner) const
{
	const auto provinceOwnerItr = ownersMap.find(provNum);
	return (provinceOwnerItr != ownersMap.end()) && (provinceOwnerItr->second == stateOwner);
}


bool HoI4::States::isProvinceNotAlreadyAssigned(int provNum) const
{
	return !assignedProvinces.count(provNum);
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
	 const std::vector<std::shared_ptr<Country>>& greatPowers,
	 double greatestStrength)
{
	Log(LogLevel::Info) << "\tConverting capital VPs";

	addBasicCapitalVPs(countries);
	addGreatPowerVPs(greatPowers);
	addStrengthVPs(countries, greatestStrength);
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


void HoI4::States::addBasicCapitalVPs(const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	for (const auto& country: countries)
	{
		if (auto capitalState = states.find(*country.second->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.addVictoryPointValue(5);
		}
	}
}


void HoI4::States::addGreatPowerVPs(const std::vector<std::shared_ptr<Country>>& greatPowers)
{
	for (const auto& greatPower: greatPowers)
	{
		if (auto capitalState = states.find(*greatPower->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.addVictoryPointValue(5);
		}
	}
}


void HoI4::States::addStrengthVPs(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 double greatestStrength)
{
	for (const auto& country: countries)
	{
		const auto VPs = calculateStrengthVPs(*country.second, greatestStrength);
		if (auto capitalState = states.find(*country.second->getCapitalState()); capitalState != states.end())
		{
			capitalState->second.addVictoryPointValue(VPs);
		}
	}
}


int HoI4::States::calculateStrengthVPs(const Country& country, double greatestStrength)
{
	const auto relativeStrength = country.getStrengthOverTime(1.0) / greatestStrength;
	return static_cast<int>(relativeStrength * 30.0);
}