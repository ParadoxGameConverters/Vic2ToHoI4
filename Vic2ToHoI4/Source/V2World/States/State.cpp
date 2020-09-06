#include "State.h"
#include "../Country.h"
#include "../Provinces/Province.h"



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
	std::list<std::shared_ptr<Vic2::Province>> provincesOrderedByPopulation;
	for (const auto& province: provinces)
	{
		provincesOrderedByPopulation.insert(
			 std::upper_bound(provincesOrderedByPopulation.begin(),
				  provincesOrderedByPopulation.end(),
				  province,
				  [](const std::shared_ptr<Vic2::Province> a, const std::shared_ptr<Vic2::Province> b) {
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
			foreignControlledProvinces.push_back(std::make_pair(province->getNumber(), province->getController()));
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