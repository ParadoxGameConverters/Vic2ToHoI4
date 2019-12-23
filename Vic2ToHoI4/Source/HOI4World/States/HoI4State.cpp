/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "HoI4State.h"
#include "StateCategories.h"
#include "../CoastalProvinces.h"
#include "../../Configuration.h"
#include "../../V2World/Province.h"
#include "../../V2World/State.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include <iomanip>
#include <ios>
#include <fstream>
#include <random>



const int POPULATION_PER_STATE_SLOT = 120000;



HoI4::State::State(const Vic2::State* _sourceState, int _ID, const std::string& _ownerTag):
	sourceState(_sourceState),
	ID(_ID),
	ownerTag(_ownerTag)
{}


void HoI4::State::output(std::ostream& out, const Configuration& theConfiguration) const
{
	out << "\n";
	out << "state={" << "\n";
	out << "\tid=" << ID << "\n";
	out << "\tname=\"STATE_" << ID << "\"\n";
	if (resources.size() > 0)
	{
		out << "\tresources={\n";
		out << std::fixed;
		out << std::setprecision(3);
		for (auto resource: resources)
		{
			out << "\t\t" << resource.first << "=" << resource.second << "\n";
		}
		out << "\t}\n";
	}
	if (impassable)
	{
		out << "\timpassable = yes\n";
	}
	out << "\n";
	out << "\thistory={\n";
	if (!ownerTag.empty())
	{
		out << "\t\towner = " << ownerTag << "\n";
	}
	if (!impassable)
	{
		if ((victoryPointValue > 0) && (victoryPointPosition))
		{
			if (theConfiguration.getDebug())
			{
				out << "\t\tvictory_points = {\n";
				out << "\t\t\t" << *victoryPointPosition << " " << (victoryPointValue + 10) << "\n";
				out << "\t\t}\n";
				for (auto VP : debugVictoryPoints)
				{
					if (VP == victoryPointPosition)
					{
						continue;
					}
					out << "\t\tvictory_points = { " << VP << " 5\n";
					out << "\t}\n";
				}
				for (auto VP : secondaryDebugVictoryPoints)
				{
					if (VP == victoryPointPosition)
					{
						continue;
					}
					out << "\t\tvictory_points = { " << VP << " 1 }\n";
				}
			}
			else
			{
				out << "\t\tvictory_points = {\n";
				out << "\t\t\t" << *victoryPointPosition << " " << victoryPointValue << " \n";
				out << "\t\t}\n";
			}
		}
	}
	if (!impassable)
	{
		out << "\t\tbuildings = {\n";
		out << "\t\t\tinfrastructure = " << infrastructure << "\n";
		out << "\t\t\tindustrial_complex = " << civFactories << "\n";
		out << "\t\t\tarms_factory = " << milFactories << "\n";
		if (dockyards > 0)
		{
			out << "\t\t\tdockyard = " << dockyards << "\n";
		}

		for (auto navalBase : navalBases)
		{
			out << "\t\t\t" << navalBase.first << " = {\n";
			out << "\t\t\t\tnaval_base = " << navalBase.second << "\n";
			out << "\t\t\t}\n";
		}

		out << "\t\t\tair_base = " << airbaseLevel << "\n";
		out << "\n";
		out << "\t\t}\n";
	}
	for (auto core: cores)
	{
		out << "\t\tadd_core_of = " << core << "\n";
	}
	for (auto countryControlledProvinces: controlledProvinces)
	{
		out << "\t\t" << countryControlledProvinces.first << " = {\n";
		for (auto province : countryControlledProvinces.second)
		{
			out << "\t\t\tset_province_controller = " << province << "\n";
		}
		out << "\t\t}\n";
	}
	out << "\t}\n";
	out << "\n";
	out << "\tprovinces={\n";
	out << "\t\t";
	for (auto provnum : provinces)
	{
		out << provnum << " ";
	}
	out << "\n";
	out << "\t}\n";
	out << "\tmanpower=" << manpower << "\n";
	out << "\tbuildings_max_level_factor=1.000\n";
	out << "\tstate_category="<< category << "\n";
	out << "}\n";
}


void HoI4::State::convertNavalBases(
	const coastalProvinces& theCoastalProvinces,
	const provinceMapper& theProvinceMapper
) {
	for (auto sourceProvince: sourceState->getProvinces())
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


std::optional<int> HoI4::State::determineNavalBaseLocation(
	const Vic2::Province& sourceProvince,
	const coastalProvinces& theCoastalProvinces,
	const provinceMapper& theProvinceMapper
) const {
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


void HoI4::State::convertControlledProvinces(
	const provinceMapper& theProvinceMapper,
	const CountryMapper& countryMapper
) {
	for (auto sourceProvince: sourceState->getProvinces())
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


bool HoI4::State::assignVPFromVic2Province(int Vic2ProvinceNumber, const provinceMapper& theProvinceMapper)
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


void HoI4::State::tryToCreateVP(const provinceMapper& theProvinceMapper, const Configuration& theConfiguration)
{
	bool VPCreated = false;

	auto vic2CapitalProvince = sourceState->getCapitalProvince();
	if (vic2CapitalProvince)
	{
		VPCreated = assignVPFromVic2Province(*vic2CapitalProvince, theProvinceMapper);
	}

	if (!VPCreated)
	{
		if (theConfiguration.getDebug() && !sourceState->isPartialState() && !impassable && !hadImpassablePart)
		{
			LOG(LogLevel::Warning) << "Could not initially create VP for state " << ID << ", but state is not split.";
		}
		for (auto province: sourceState->getProvinces())
		{
			if (
				 (province->getPopulation("aristocrats") > 0) ||
				 (province->getPopulation("bureaucrats") > 0) ||
				 (province->getPopulation("capitalists") > 0)
			) {
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
		for (auto province: sourceState->getProvinces())
		{
			provincesOrderedByPopulation.insert(
				std::upper_bound(	provincesOrderedByPopulation.begin(),
										provincesOrderedByPopulation.end(),
										province,
										[](const Vic2::Province* a, const Vic2::Province* b){
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
		LOG(LogLevel::Warning) << "Could not create VP for state " << ID;
	}

	addDebugVPs(theProvinceMapper);
}


void HoI4::State::addDebugVPs(const provinceMapper& theProvinceMapper)
{
	for (auto sourceProvinceNum: sourceState->getProvinceNums())
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


void HoI4::State::addManpower(const provinceMapper& theProvinceMapper, const Configuration& theConfiguration)
{
	for (auto sourceProvince: sourceState->getProvinces())
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
			manpower += static_cast<int>(sourceProvince->getTotalPopulation() * 4 * theConfiguration.getManpowerFactor());
		}
	}
}


void HoI4::State::convertIndustry(
	double workerFactoryRatio,
	const HoI4::StateCategories& theStateCategories,
	const coastalProvinces& theCoastalProvinces
) {
	int factories = determineFactoryNumbers(workerFactoryRatio);

	determineCategory(factories, theStateCategories);
	setInfrastructure(factories);
	setIndustry(factories, theCoastalProvinces);
	addVictoryPointValue(factories / 2);
}


int HoI4::State::determineFactoryNumbers(double workerFactoryRatio) const
{
	double rawFactories = sourceState->getEmployedWorkers() * workerFactoryRatio;
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

	int population = sourceState->getPopulation();
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


void HoI4::State::setInfrastructure(int factories)
{
	infrastructure = 3;
	infrastructure += sourceState->getAverageRailLevel() / 2;

	if (factories > 4)
	{
		infrastructure++;
	}
	if (factories > 6)
	{
		infrastructure++;
	}
	if (factories > 10)
	{
		infrastructure++;
	}
}


static std::mt19937 randomnessEngine;
static std::uniform_int_distribution<> numberDistributor(0, 99);
void HoI4::State::setIndustry(int factories, const coastalProvinces& theCoastalProvinces)
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


bool HoI4::State::amICoastal(const coastalProvinces& theCoastalProvinces) const
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