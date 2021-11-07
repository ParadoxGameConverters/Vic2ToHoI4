#include "State.h"
#include "V2World/Countries/Country.h"
#include "V2World/Provinces/Province.h"
#include <list>



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


constexpr float WORKERS_PER_FACTORY_LEVEL = 10000.0F;
Vic2::workerStruct Vic2::State::limitWorkersByFactoryLevels(const workerStruct& workers) const
{
	if ((workers.craftsmen + workers.clerks) <= (static_cast<float>(factoryLevel) * 10000.0F))
	{
		return workers;
	}

	auto newWorkers = workers;
	newWorkers.craftsmen = (static_cast<float>(factoryLevel) * WORKERS_PER_FACTORY_LEVEL) /
								  (workers.craftsmen + workers.clerks) * workers.craftsmen;
	newWorkers.clerks = (static_cast<float>(factoryLevel) * WORKERS_PER_FACTORY_LEVEL) /
							  (workers.craftsmen + workers.clerks) * workers.clerks;
	return newWorkers;
}


int Vic2::State::determineEmployedWorkersScore(const workerStruct& workers)
{
	return static_cast<int>(
		 workers.craftsmen + (workers.clerks * 2) + (workers.artisans / 2) + (workers.capitalists * 2));
}


void Vic2::State::eatState(const State& state, const StateDefinitions& stateDefinitions)
{
	provinceNumbers.insert(state.provinceNumbers.begin(), state.provinceNumbers.end());
	provinces.insert(provinces.end(), state.provinces.begin(), state.provinces.end());

	partialState = false;
	for (const auto provinceNumber: stateDefinitions.getAllProvinces(*provinceNumbers.begin()))
	{
		if (!provinceNumbers.contains(provinceNumber))
		{
			partialState = true;
			break;
		}
	}

	factoryLevel += state.factoryLevel;
	determineEmployedWorkers();
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
		return 0.0F;
	}

	auto totalRailLevel = 0;
	for (const auto& province: provinces)
	{
		totalRailLevel += province->getRailLevel();
	}
	return static_cast<float>(totalRailLevel) / provinces.size();
}


std::optional<int> Vic2::State::getUpperClassLocation() const
{
	for (const auto& province: provinces)
	{
		if ((province->getPopulation("aristocrats") > 0) || (province->getPopulation("bureaucrats") > 0) ||
			 (province->getPopulation("capitalists") > 0))
		{
			return province->getNumber();
		}
	}

	return std::nullopt;
}


std::vector<int> Vic2::State::getProvincesOrderedByPopulation() const
{
	std::list<std::shared_ptr<Province>> provincesOrderedByPopulation;
	for (const auto& province: provinces)
	{
		provincesOrderedByPopulation.insert(
			 std::ranges::upper_bound(provincesOrderedByPopulation,
			                          province,
			                          [](const std::shared_ptr<Province>& a, const std::shared_ptr<Province>& b) {
				                          // provide a 'backwards' comparison to force the sort order we want
				                          return a->getTotalPopulation() > b->getTotalPopulation();
			                          }),
			 province);
	}

	std::vector<int> provinceNumbersOrderedByPopulation;
	for (const auto& province: provincesOrderedByPopulation)
	{
		provinceNumbersOrderedByPopulation.push_back(province->getNumber());
	}

	return provinceNumbersOrderedByPopulation;
}


std::vector<std::pair<int, std::string>> Vic2::State::getForeignControlledProvinces() const
{
	std::vector<std::pair<int, std::string>> foreignControlledProvinces;
	for (const auto& province: provinces)
	{
		if (province->getOwner() != province->getController())
		{
			foreignControlledProvinces.emplace_back(std::make_pair(province->getNumber(), province->getController()));
		}
	}

	return foreignControlledProvinces;
}


std::map<int, int> Vic2::State::getNavalBases() const
{
	std::map<int, int> navalBases;
	for (const auto& province: provinces)
	{
		if (const auto level = province->getNavalBaseLevel(); level > 0)
		{
			navalBases[province->getNumber()] = level;
		}
	}

	return navalBases;
}