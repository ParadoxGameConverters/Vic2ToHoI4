#include "State.h"
#include "../Building.h"
#include "../Country.h"
#include "../Province.h"



void Vic2::State::determineEmployedWorkers()
{
	auto workers = countEmployedWorkers();
	workers = limitWorkersByFactoryLevels(workers);
	employedWorkers = determineEmployedWorkersScore(workers);
}


Vic2::workerStruct Vic2::State::countEmployedWorkers() const
{
	workerStruct workers;

	for (const auto& province: provinces)
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
	if ((workers.craftsmen + workers.clerks) <= (factoryLevel * 10000))
	{
		return workers;
	}

	workerStruct newWorkers;
	newWorkers.craftsmen = (factoryLevel * 10000) / (workers.craftsmen + workers.clerks) * workers.craftsmen;
	newWorkers.clerks = (factoryLevel * 10000) / (workers.craftsmen + workers.clerks) * workers.clerks;
	newWorkers.artisans = workers.artisans;
	return newWorkers;
}


int Vic2::State::determineEmployedWorkersScore(const workerStruct& workers) const
{
	auto employedWorkerScore =
		 workers.craftsmen + (workers.clerks * 2) + (workers.artisans / 2) + (workers.capitalists * 2);
	if (ownerHasNoCores())
	{
		employedWorkerScore /= 2;
	}

	return employedWorkerScore;
}


bool Vic2::State::ownerHasNoCores() const
{
	for (const auto& province: provinces)
	{
		for (const auto& country: province->getCores())
		{
			if (country == owner)
			{
				return false;
			}
		}
	}

	return true;
}


int Vic2::State::getPopulation() const
{
	auto population = 0;
	for (const auto& province: provinces)
	{
		population += province->getPopulation();
	}

	return population;
}


float Vic2::State::getAverageRailLevel() const
{
	if (provinces.empty())
	{
		return 0.0f;
	}

	int totalRailLevel = 0;
	for (const auto& province: provinces)
	{
		totalRailLevel += province->getRailLevel();
	}
	return static_cast<float>(totalRailLevel) / provinces.size();
}