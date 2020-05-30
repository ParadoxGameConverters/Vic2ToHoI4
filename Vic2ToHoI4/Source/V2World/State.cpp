#include "State.h"
#include "Building.h"
#include "Country.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "Province.h"
#include "StateDefinitions.h"
#include "World.h"



Vic2::State::State(std::istream& theStream,
	 const std::string& ownerTag,
	 const Vic2::StateDefinitions& theStateDefinitions):
	 owner(ownerTag)
{
	registerKeyword("provinces", [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList provinceList(theStream);
		for (auto province: provinceList.getInts())
		{
			provinceNums.insert(province);
		}
	});
	registerKeyword("state_buildings", [this](const std::string& unused, std::istream& theStream) {
		Building theBuilding(theStream);
		factoryLevel += theBuilding.getLevel();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	setID(theStateDefinitions);
	setCapital(theStateDefinitions);
}


Vic2::State::State(std::set<std::pair<int, Vic2::Province*>> theProvinces, const StateDefinitions& theStateDefinitions)
{
	for (auto province: theProvinces)
	{
		provinceNums.insert(province.first);
		provinces.insert(province.second);
	}
	setID(theStateDefinitions);
	determineIfPartialState(theStateDefinitions);
	setCapital(theStateDefinitions);
}


void Vic2::State::setID(const Vic2::StateDefinitions& theStateDefinitions)
{
	auto foundStateID = theStateDefinitions.getStateID(*provinceNums.begin());
	if (foundStateID)
	{
		stateID = *foundStateID;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not find the state for Vic2 province " << *provinceNums.begin() << ".";
	}
}


void Vic2::State::setCapital(const Vic2::StateDefinitions& theStateDefinitions)
{
	capitalProvince = theStateDefinitions.getCapitalProvince(stateID);
}


void Vic2::State::determineEmployedWorkers()
{
	workerStruct workers = countEmployedWorkers();
	workers = limitWorkersByFactoryLevels(workers);
	employedWorkers = determineEmployedWorkersScore(workers);
}


Vic2::workerStruct Vic2::State::countEmployedWorkers() const
{
	workerStruct workers;

	for (auto province: provinces)
	{
		workers.craftsmen += province->getPopulation("craftsmen");
		workers.clerks += province->getPopulation("clerks");
		workers.artisans += province->getPopulation("artisans");
		workers.capitalists += province->getLiteracyWeightedPopulation("capitalists");
	}

	return workers;
}


Vic2::workerStruct Vic2::State::limitWorkersByFactoryLevels(const workerStruct& workers) const
{
	workerStruct newWorkers;
	if ((workers.craftsmen + workers.clerks) > (factoryLevel * 10000))
	{
		newWorkers.craftsmen =
			 static_cast<int>((factoryLevel * 10000.0f) / (workers.craftsmen + workers.clerks) * workers.craftsmen);
		newWorkers.clerks =
			 static_cast<int>((factoryLevel * 10000.0f) / (workers.craftsmen + workers.clerks) * workers.clerks);
		newWorkers.artisans = workers.artisans;
	}
	else
	{
		newWorkers = workers;
	}

	return newWorkers;
}


int Vic2::State::determineEmployedWorkersScore(const workerStruct& workers) const
{
	int employedWorkerScore =
		 workers.craftsmen + (workers.clerks * 2) + static_cast<int>(workers.artisans * 0.5) + (workers.capitalists * 2);
	if (ownerHasNoCores())
	{
		employedWorkerScore /= 2;
	}

	return employedWorkerScore;
}


bool Vic2::State::ownerHasNoCores() const
{
	for (auto province: provinces)
	{
		for (auto country: province->getCores())
		{
			if (country == owner)
			{
				return false;
			}
		}
	}

	return true;
}


void Vic2::State::determineIfPartialState(const StateDefinitions& theStateDefinitions)
{
	if (provinces.size() > 0)
	{
		for (auto expectedProvince: theStateDefinitions.getAllProvinces(*provinceNums.begin()))
		{
			if (provinceNums.count(expectedProvince) == 0)
			{
				partialState = true;
				break;
			}
		}
	}
}


int Vic2::State::getPopulation() const
{
	int population = 0;
	for (auto province: provinces)
	{
		population += province->getPopulation();
	}

	return population;
}


float Vic2::State::getAverageRailLevel() const
{
	float totalRailLevel = 0;
	for (auto province: provinces)
	{
		totalRailLevel += province->getRailLevel();
	}

	if (provinces.size() > 0)
	{
		return (totalRailLevel / provinces.size());
	}
	else
	{
		return 0.0f;
	}
}
