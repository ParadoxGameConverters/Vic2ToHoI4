#include "State.h"
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
		workers.craftsmen += static_cast<float>(province->getPopulation("craftsmen"));
		workers.clerks += static_cast<float>(province->getPopulation("clerks"));
		workers.artisans += static_cast<float>(province->getPopulation("artisans"));
		workers.capitalists += static_cast<float>(province->getLiteracyWeightedPopulation("capitalists"));
	}

	return workers;
}


Vic2::workerStruct Vic2::State::limitWorkersByFactoryLevels(const workerStruct& workers) const
{
	if ((workers.craftsmen + workers.clerks) <= (static_cast<float>(factoryLevel) * 10000.0f))
	{
		return workers;
	}

	auto newWorkers = workers;
	newWorkers.craftsmen =
		 (static_cast<float>(factoryLevel) * 10000.0f) / (workers.craftsmen + workers.clerks) * workers.craftsmen;
	newWorkers.clerks =
		 (static_cast<float>(factoryLevel) * 10000.0f) / (workers.craftsmen + workers.clerks) * workers.clerks;
	return newWorkers;
}


int Vic2::State::determineEmployedWorkersScore(const workerStruct& workers)
{
	return static_cast<int>(
		 workers.craftsmen + (workers.clerks * 2) + (workers.artisans / 2) + (workers.capitalists * 2));
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

	auto totalRailLevel = 0;
	for (const auto& province: provinces)
	{
		totalRailLevel += province->getRailLevel();
	}
	return static_cast<float>(totalRailLevel) / provinces.size();
}