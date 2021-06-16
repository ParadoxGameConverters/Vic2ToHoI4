#include "HoI4State.h"
#include "HOI4World/Map/CoastalProvinces.h"
#include "Log.h"
#include "StateCategories.h"
#include "V2World/Provinces/Province.h"
#include "V2World/States/State.h"



constexpr int POP_CONVERSION_FACTOR = 4;
constexpr int POPULATION_PER_STATE_SLOT = 120000;
constexpr int FIRST_INFRASTRUCTURE_REWARD_LEVEL = 4;
constexpr int SECOND_INFRASTRUCTURE_REWARD_LEVEL = 6;
constexpr int THIRD_INFRASTRUCTURE_REWARD_LEVEL = 10;



HoI4::State::State(const Vic2::State& sourceState, int _ID, const std::string& _ownerTag): ID(_ID), ownerTag(_ownerTag)
{
	population = sourceState.getPopulation();
	employedWorkers = sourceState.getEmployedWorkers();

	if (ownerTag.empty())
	{
		infrastructure = 0;
	}
	addInfrastructureFromRails(sourceState.getAverageRailLevel());
}


void HoI4::State::convertNavalBases(const std::map<int, int>& sourceNavalBases,
	 const CoastalProvinces& theCoastalProvinces,
	 const Mappers::ProvinceMapper& theProvinceMapper)
{
	for (const auto& sourceNavalBase: sourceNavalBases)
	{
		int navalBaseLevel = determineNavalBaseLevel(sourceNavalBase.second);
		if (navalBaseLevel == 0)
		{
			continue;
		}

		auto navalBaseLocation =
			 determineNavalBaseLocation(sourceNavalBase.first, theCoastalProvinces, theProvinceMapper);
		if (navalBaseLocation)
		{
			addNavalBase(navalBaseLevel, *navalBaseLocation);
		}
	}

	if (navalBases.empty())
	{
		for (const auto& province: provinces)
		{
			if (theCoastalProvinces.isProvinceCoastal(province))
			{
				addNavalBase(1, province);
				break;
			}
		}
	}
}


int HoI4::State::determineNavalBaseLevel(int sourceLevel)
{
	int navalBaseLevel = sourceLevel * 2;
	if (navalBaseLevel > 10)
	{
		navalBaseLevel = 10;
	}

	return navalBaseLevel;
}


std::optional<int> HoI4::State::determineNavalBaseLocation(int sourceProvince,
	 const CoastalProvinces& theCoastalProvinces,
	 const Mappers::ProvinceMapper& theProvinceMapper)
{
	for (auto HoI4ProvNum: theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince))
	{
		if (theCoastalProvinces.isProvinceCoastal(HoI4ProvNum))
		{
			return HoI4ProvNum;
		}
	}

	return std::nullopt;
}


void HoI4::State::addNavalBase(int level, int location)
{
	if ((level > 0) && provinces.contains(location))
	{
		navalBases[location] = level;
	}
}


void HoI4::State::addCores(const std::set<std::string>& newCores)
{
	for (auto newCore: newCores)
	{
		cores.insert(newCore);
		if (claims.contains(newCore))
		{
			claims.erase(newCore);
		}
	}
}


void HoI4::State::addClaims(const std::set<std::string>& newClaims)
{
	for (const auto& claim: newClaims)
	{
		claims.insert(claim);
	}
}


void HoI4::State::convertControlledProvinces(const std::vector<std::pair<int, std::string>>& foreignControlledProvinces,
	 const Mappers::ProvinceMapper& theProvinceMapper,
	 const Mappers::CountryMapper& countryMapper)
{
	for (const auto& foreignControlledProvince: foreignControlledProvinces)
	{
		auto possibleController = countryMapper.getHoI4Tag(foreignControlledProvince.second);
		if ((!possibleController) || (*possibleController == "REB"))
		{
			continue;
		}

		for (auto destinationProvince: theProvinceMapper.getVic2ToHoI4ProvinceMapping(foreignControlledProvince.first))
		{
			if (!provinces.contains(destinationProvince))
			{
				continue;
			}

			if (!controlledProvinces.contains(*possibleController))
			{
				std::set<int> destinationProvinces;
				destinationProvinces.insert(destinationProvince);
				controlledProvinces.insert(std::make_pair(*possibleController, destinationProvinces));
			}
			else
			{
				controlledProvinces.find(*possibleController)->second.insert(destinationProvince);
			}
		}
	}
}


void HoI4::State::removeControlledProvince(int provinceNum)
{
	for (auto& [owner, controlledProvinces]: controlledProvinces)
	{
		controlledProvinces.erase(provinceNum);
	}
}


void HoI4::State::setControlledProvince(int provinceNum, const std::string& country)
{
	if (country == ownerTag)
	{
		return;
	}

	auto [existing, inserted] = controlledProvinces.insert(std::make_pair(country, std::set{provinceNum}));
	if (!inserted)
	{
		existing->second.insert(provinceNum);
	}
}


bool HoI4::State::assignVPFromVic2Province(int Vic2ProvinceNumber, const Mappers::ProvinceMapper& theProvinceMapper)
{
	for (auto province: theProvinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNumber))
	{
		if (isProvinceInState(province))
		{
			assignVP(province);
			return true;
		}
	}

	return false;
}


void HoI4::State::assignVP(int location)
{
	victoryPointPosition = location;

	if (cores.contains(ownerTag))
	{
		victoryPointValue += 1;
	}
}


std::optional<int> HoI4::State::getMainNavalLocation() const
{
	std::optional<int> mainLocation;
	int mainSize = 0;
	for (const auto& navalBase: navalBases)
	{
		if (navalBase.second > mainSize)
		{
			mainLocation = navalBase.first;
			mainSize = navalBase.second;
		}
	}

	return mainLocation;
}


int HoI4::State::getManpower() const
{
	if (manpower == 0)
	{
		return 1;
	}

	return manpower;
}



void HoI4::State::tryToCreateVP(const Vic2::State& sourceState,
	 const Mappers::ProvinceMapper& theProvinceMapper,
	 const Configuration& theConfiguration)
{
	bool VPCreated = false;

	auto vic2CapitalProvince = sourceState.getCapitalProvince();
	if (vic2CapitalProvince)
	{
		VPCreated = assignVPFromVic2Province(*vic2CapitalProvince, theProvinceMapper);
	}

	if (!VPCreated)
	{
		if (theConfiguration.getDebug() && !sourceState.isPartialState() && !impassable && !hadImpassablePart)
		{
			Log(LogLevel::Warning) << "Could not initially create VP for state " << ID << ", but state is not split.";
		}
		auto vic2UpperClassProvince = sourceState.getUpperClassLocation();
		if (vic2UpperClassProvince)
		{
			VPCreated = assignVPFromVic2Province(*vic2UpperClassProvince, theProvinceMapper);
		}
	}

	if (!VPCreated)
	{
		for (const auto& province: sourceState.getProvincesOrderedByPopulation())
		{
			VPCreated = assignVPFromVic2Province(province, theProvinceMapper);
			if (VPCreated)
			{
				break;
			}
		}
	}

	if (!VPCreated)
	{
		Log(LogLevel::Warning) << "Could not create VP for state " << ID;
	}

	addDebugVPs(sourceState, theProvinceMapper);
}


void HoI4::State::addDebugVPs(const Vic2::State& sourceState, const Mappers::ProvinceMapper& theProvinceMapper)
{
	for (auto sourceProvinceNum: sourceState.getProvinceNumbers())
	{
		auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvinceNum);
		if (!mapping.empty() && isProvinceInState(mapping[0]))
		{
			debugVictoryPoints.insert(mapping[0]);
		}
		for (auto province: mapping)
		{
			secondaryDebugVictoryPoints.insert(province);
		}
	}
}


void HoI4::State::addManpower(const std::set<std::shared_ptr<Vic2::Province>>& sourceProvinces,
	 const Mappers::ProvinceMapper& theProvinceMapper,
	 const Configuration& theConfiguration)
{
	for (auto sourceProvince: sourceProvinces)
	{
		int numProvincesInState = 0;
		int numProvincesInMapping = 0;
		auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince->getNumber());

		numProvincesInMapping = static_cast<int>(mapping.size());
		for (auto HoI4Province: mapping)
		{
			if (isProvinceInState(HoI4Province))
			{
				numProvincesInState++;
			}
		}


		if (numProvincesInMapping && numProvincesInState)
		{
			manpower +=
				 static_cast<int>(sourceProvince->getTotalPopulation() * POP_CONVERSION_FACTOR *
										theConfiguration.getManpowerFactor() * numProvincesInState / numProvincesInMapping);
		}
	}
}


void HoI4::State::convertIndustry(double workerFactoryRatio,
	 const HoI4::StateCategories& theStateCategories,
	 const CoastalProvinces& theCoastalProvinces)
{
	int factories = determineFactoryNumbers(workerFactoryRatio);

	determineCategory(factories, theStateCategories);
	addInfrastructureFromFactories(factories);
	setIndustry(factories, theCoastalProvinces);
	addVictoryPointValue(factories / 2);
}


int HoI4::State::determineFactoryNumbers(double workerFactoryRatio) const
{
	double rawFactories = employedWorkers * workerFactoryRatio;
	rawFactories = round(rawFactories);
	return constrainFactoryNumbers(rawFactories);
}


int HoI4::State::constrainFactoryNumbers(double rawFactories) const
{
	int factories = static_cast<int>(rawFactories);

	int upperLimit = 12;
	if (capitalState)
	{
		upperLimit = 11;
	}

	if (factories < 0)
	{
		factories = 0;
	}
	else if (factories > upperLimit)
	{
		factories = upperLimit;
	}

	return factories;
}


void HoI4::State::determineCategory(int factories, const HoI4::StateCategories& theStateCategories)
{
	if (capitalState)
	{
		factories++;
	}

	int stateSlots = population / POPULATION_PER_STATE_SLOT;
	if (factories >= stateSlots)
	{
		stateSlots = factories + 2;
	}

	if (!impassable)
	{
		category = theStateCategories.getBestCategory(stateSlots);
	}
}


void HoI4::State::addInfrastructureFromRails(float averageRailLevels)
{
	infrastructure += static_cast<int>(averageRailLevels / 2);
}


void HoI4::State::addInfrastructureFromFactories(int factories)
{
	if (factories > FIRST_INFRASTRUCTURE_REWARD_LEVEL)
	{
		infrastructure++;
	}
	if (factories > SECOND_INFRASTRUCTURE_REWARD_LEVEL)
	{
		infrastructure++;
	}
	if (factories > THIRD_INFRASTRUCTURE_REWARD_LEVEL)
	{
		infrastructure++;
	}
}


void HoI4::State::setIndustry(int factories, const CoastalProvinces& theCoastalProvinces)
{
	if (ownerHasNoCore())
	{
		factories /= 2;
	}

	struct factoriesStruct
	{
		double military;
		double civilian;
		double docks;
	};
	static std::unordered_map<std::string, factoriesStruct> accumulator;
	if (accumulator.find(ownerTag) == accumulator.end())
	{
		accumulator[ownerTag] = {0, 0, 0};
	}
	auto& country = accumulator[ownerTag];

	if (amICoastal(theCoastalProvinces))
	{
		//		20% chance of dockyard
		//		57% chance of civilian factory
		//		23% chance of military factory
		country.military += 0.23 * factories;
		country.civilian += 0.57 * factories;
		country.docks += 0.20 * factories;
	}
	else
	{
		//		 0% chance of dockyard
		//		71% chance of civilian factory
		//		29% chance of military factory
		country.military += 0.29 * factories;
		country.civilian += 0.71 * factories;
	}

	for (int i = 0; i < factories; i++)
	{
		if (amICoastal(theCoastalProvinces) && (country.docks > 0.0))
		{
			dockyards++;
			country.docks -= 1.0;
		}
		else if (country.military >= 0.0)
		{
			milFactories++;
			country.military -= 1.0;
		}
		else
		{
			civFactories++;
			country.civilian -= 1.0;
		}
	}
}


bool HoI4::State::amICoastal(const CoastalProvinces& theCoastalProvinces) const
{
	auto coastalProvinces = theCoastalProvinces.getCoastalProvinces();
	for (auto province: provinces)
	{
		if (coastalProvinces.contains(province))
		{
			return true;
		}
	}

	return false;
}


bool HoI4::State::ownerHasNoCore() const
{
	return !cores.contains(ownerTag);
}


bool HoI4::State::isProvinceInState(int provinceNum) const
{
	return provinces.contains(provinceNum);
}