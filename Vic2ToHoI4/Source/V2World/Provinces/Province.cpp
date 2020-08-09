#include "Province.h"
#include "ParserHelpers.h"



Vic2::Province::Province(const std::string& numberString,
	 std::istream& theStream,
	 Pop::Factory& popFactory):
	 number(stoi(numberString))
{
	registerKeyword("owner", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ownerSingleString(theStream);
		owner = ownerSingleString.getString();
	});
	registerKeyword("core", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString coreString(theStream);
		auto newCoreString = coreString.getString();
		cores.insert(newCoreString);
	});
	registerKeyword("controller", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString controllerSingleString(theStream);
		controller = controllerSingleString.getString();
	});
	registerKeyword("naval_base", [this](const std::string& unused, std::istream& theStream) {
		commonItems::doubleList navalBaseSizeList(theStream);
		navalBaseLevel = static_cast<int>(navalBaseSizeList.getDoubles()[0]);
	});
	registerKeyword("railroad", [this](const std::string& unused, std::istream& theStream) {
		commonItems::doubleList railSizeList(theStream);
		railLevel = static_cast<int>(railSizeList.getDoubles()[0]);
	});
	registerRegex(
		 "aristocrats|artisans|bureaucrats|capitalists|clergymen|craftsmen|clerks|farmers|soldiers|officers|labourers|"
		 "slaves|serfs",
		 [this, &popFactory](const std::string& popType, std::istream& theStream) {
			 pops.push_back(*popFactory.getPop(popType, theStream));
		 });
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}


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
