#include "HoI4State.h"
#include "../../V2World/Province.h"
#include "../../V2World/State.h"
#include "../Map/CoastalProvinces.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "StateCategories.h"
#include <random>



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


void HoI4::State::convertNavalBases(const std::set<const Vic2::Province*>& sourceProvinces,
	 const CoastalProvinces& theCoastalProvinces,
	 const mappers::ProvinceMapper& theProvinceMapper)
{
	for (auto sourceProvince: sourceProvinces)
	{
		int navalBaseLevel = determineNavalBaseLevel(*sourceProvince);
		if (navalBaseLevel == 0)
		{
			continue;
		}

		auto navalBaseLocation = determineNavalBaseLocation(*sourceProvince, theCoastalProvinces, theProvinceMapper);
		if (navalBaseLocation)
		{
			addNavalBase(navalBaseLevel, *navalBaseLocation);
		}
	}
}


int HoI4::State::determineNavalBaseLevel(const Vic2::Province& sourceProvince) const
{
	int navalBaseLevel = sourceProvince.getNavalBaseLevel() * 2;
	if (navalBaseLevel > 10)
	{
		navalBaseLevel = 10;
	}

	return navalBaseLevel;
}


std::optional<int> HoI4::State::determineNavalBaseLocation(const Vic2::Province& sourceProvince,
	 const CoastalProvinces& theCoastalProvinces,
	 const mappers::ProvinceMapper& theProvinceMapper) const
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince.getNumber()))
	{
		for (auto HoI4ProvNum: *mapping)
		{
			if (theCoastalProvinces.isProvinceCoastal(HoI4ProvNum))
			{
				return HoI4ProvNum;
			}
		}
	}

	return {};
}


void HoI4::State::addNavalBase(int level, int location)
{
	if ((level > 0) && (provinces.find(location) != provinces.end()))
	{
		navalBases[location] = level;
	}
}


void HoI4::State::addCores(const std::set<std::string>& newCores)
{
	for (auto newCore: newCores)
	{
		cores.insert(newCore);
	}
}


void HoI4::State::convertControlledProvinces(const std::set<const Vic2::Province*>& sourceProvinces,
	 const mappers::ProvinceMapper& theProvinceMapper,
	 const CountryMapper& countryMapper)
{
	for (auto sourceProvince: sourceProvinces)
	{
		if (sourceProvince->getOwner() != sourceProvince->getController())
		{
			auto possibleController = countryMapper.getHoI4Tag(sourceProvince->getController());
			if ((!possibleController) || (*possibleController == "REB"))
			{
				continue;
			}
			auto provinceMapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince->getNumber());
			if (provinceMapping)
			{
				for (auto destinationProvince: *provinceMapping)
				{
					if (provinces.count(destinationProvince) > 0)
					{
						if (controlledProvinces.count(*possibleController) == 0)
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
		}
	}
}


bool HoI4::State::assignVPFromVic2Province(int Vic2ProvinceNumber, const mappers::ProvinceMapper& theProvinceMapper)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNumber))
	{
		for (auto province: *mapping)
		{
			if (isProvinceInState(province))
			{
				assignVP(province);
				return true;
			}
		}
	}

	return false;
}


void HoI4::State::assignVP(int location)
{
	victoryPointPosition = location;

	victoryPointValue = 1;
	if (cores.count(ownerTag) != 0)
	{
		victoryPointValue += 2;
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


void HoI4::State::tryToCreateVP(const Vic2::State& sourceState,
	 const mappers::ProvinceMapper& theProvinceMapper,
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
		for (auto province: sourceState.getProvinces())
		{
			if ((province->getPopulation("aristocrats") > 0) || (province->getPopulation("bureaucrats") > 0) ||
				 (province->getPopulation("capitalists") > 0))
			{
				VPCreated = assignVPFromVic2Province(province->getNumber(), theProvinceMapper);
				if (VPCreated)
				{
					break;
				}
			}
		}
	}

	if (!VPCreated)
	{
		std::list<const Vic2::Province*> provincesOrderedByPopulation;
		for (auto province: sourceState.getProvinces())
		{
			provincesOrderedByPopulation.insert(std::upper_bound(provincesOrderedByPopulation.begin(),
																 provincesOrderedByPopulation.end(),
																 province,
																 [](const Vic2::Province* a, const Vic2::Province* b) {
																	 // provide a 'backwards' comparison to force the sort order we want
																	 return a->getTotalPopulation() > b->getTotalPopulation();
																 }),
				 province);
		}
		for (auto province: provincesOrderedByPopulation)
		{
			VPCreated = assignVPFromVic2Province(province->getNumber(), theProvinceMapper);
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


void HoI4::State::addDebugVPs(const Vic2::State& sourceState, const mappers::ProvinceMapper& theProvinceMapper)
{
	for (auto sourceProvinceNum: sourceState.getProvinceNumbers())
	{
		auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvinceNum);
		if (mapping && (isProvinceInState((*mapping)[0])))
		{
			debugVictoryPoints.insert((*mapping)[0]);
		}
		for (auto province: *mapping)
		{
			secondaryDebugVictoryPoints.insert(province);
		}
	}
}


void HoI4::State::addManpower(const std::set<const Vic2::Province*>& sourceProvinces,
	 const mappers::ProvinceMapper& theProvinceMapper,
	 const Configuration& theConfiguration)
{
	for (auto sourceProvince: sourceProvinces)
	{
		bool provinceIsInState = false;
		if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince->getNumber()))
		{
			for (auto HoI4Province: *mapping)
			{
				if (isProvinceInState(HoI4Province))
				{
					provinceIsInState = true;
					break;
				}
			}
		}

		if (provinceIsInState)
		{
			manpower += static_cast<int>(
				 sourceProvince->getTotalPopulation() * POP_CONVERSION_FACTOR * theConfiguration.getManpowerFactor());
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


static std::mt19937 randomnessEngine;
static std::uniform_int_distribution<> numberDistributor(0, 99);
void HoI4::State::setIndustry(int factories, const CoastalProvinces& theCoastalProvinces)
{
	if (amICoastal(theCoastalProvinces))
	{
		// distribute military factories, civilian factories, and dockyards using unseeded random
		//		20% chance of dockyard
		//		57% chance of civilian factory
		//		23% chance of military factory
		for (int i = 0; i < factories; i++)
		{
			double randomNum = numberDistributor(randomnessEngine);
			if (randomNum > 76)
			{
				milFactories++;
			}
			else if (randomNum > 19)
			{
				civFactories++;
			}
			else
			{
				dockyards++;
			}
		}
	}
	else
	{
		// distribute military factories, civilian factories, and dockyards using unseeded random
		//		 0% chance of dockyard
		//		71% chance of civilian factory
		//		29% chance of military factory
		for (int i = 0; i < factories; i++)
		{
			double randomNum = numberDistributor(randomnessEngine);
			if (randomNum > 70)
			{
				milFactories++;
			}
			else
			{
				civFactories++;
			}
		}
	}
}


bool HoI4::State::amICoastal(const CoastalProvinces& theCoastalProvinces) const
{
	auto coastalProvinces = theCoastalProvinces.getCoastalProvinces();
	for (auto province: provinces)
	{
		auto itr = coastalProvinces.find(province);
		if (itr != coastalProvinces.end())
		{
			return true;
		}
	}

	return false;
}


bool HoI4::State::isProvinceInState(int provinceNum) const
{
	return (provinces.count(provinceNum) > 0);
}