#include "Province.h"



int Vic2::Province::getTotalPopulation() const
{
	return getPopulation();
}


int Vic2::Province::getPopulation(std::optional<std::string> type) const
{
	int totalPopulation = 0;
	for (auto pop: pops)
	{
		if (!type || *type == pop.getType())
		{
			totalPopulation += pop.getSize();
		}
	}

	return totalPopulation;
}


int Vic2::Province::getLiteracyWeightedPopulation(std::optional<std::string> type) const
{
	int totalPopulation = 0;
	for (auto pop: pops)
	{
		if (!type || *type == pop.getType())
		{
			totalPopulation += calculateLiteracyWeightedPop(pop);
		}
	}
	return totalPopulation;
}


double Vic2::Province::getPercentageWithCultures(const std::set<std::string>& cultures) const
{
	int totalPopulation = 0;
	int populationOfCultures = 0;

	for (auto pop: pops)
	{
		totalPopulation += pop.getSize();
		if (cultures.count(pop.getCulture()) > 0)
		{
			populationOfCultures += pop.getSize();
		}
	}

	if (totalPopulation > 0)
	{
		return 1.0 * populationOfCultures / totalPopulation;
	}
	else
	{
		return 0.0;
	}
}


int Vic2::Province::calculateLiteracyWeightedPop(const Pop& thePop) const
{
	return int(thePop.getSize() * (thePop.getLiteracy() * 0.9 + 0.1));
}
