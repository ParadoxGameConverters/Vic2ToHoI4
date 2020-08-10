#include "Province.h"



int Vic2::Province::getTotalPopulation() const
{
	return getPopulation();
}


int Vic2::Province::getPopulation(const std::optional<std::string>& type) const
{
	auto totalPopulation = 0;
	for (const auto& pop: pops)
	{
		if (!type || *type == pop.getType())
		{
			totalPopulation += pop.getSize();
		}
	}

	return totalPopulation;
}


int Vic2::Province::getLiteracyWeightedPopulation(const std::optional<std::string>& type) const
{
	auto totalPopulation = 0;
	for (const auto& pop: pops)
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
	auto totalPopulation = 0;
	auto populationOfCultures = 0;

	for (const auto& pop: pops)
	{
		totalPopulation += pop.getSize();
		if (cultures.count(pop.getCulture()))
		{
			populationOfCultures += pop.getSize();
		}
	}

	if (totalPopulation <= 0)
	{
		return 0.0;
	}
	return 1.0 * populationOfCultures / totalPopulation;
}


constexpr float minimumLiteracyWeighting = 0.1f;
constexpr float literacyWeighting = 0.9f;
int Vic2::Province::calculateLiteracyWeightedPop(const Pop& thePop)
{
	return int(thePop.getSize() * (thePop.getLiteracy() * literacyWeighting + minimumLiteracyWeighting));
}
