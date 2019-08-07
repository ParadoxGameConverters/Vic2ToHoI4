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



#include "Province.h"
#include "Log.h"
#include "ParserHelpers.h"
#include <memory>



Vic2::Province::Province(const std::string& numberString, std::istream& theStream):
	number(stoi(numberString))
{
	registerKeyword(std::regex("owner"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ownerSingleString(theStream);
		owner = ownerSingleString.getString();
	});
	registerKeyword(std::regex("core"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString coreString(theStream);
		auto newCoreString = coreString.getString();
		cores.insert(newCoreString);
	});
	registerKeyword(std::regex("fort"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::doubleList fortSizeList(theStream);
		fortLevel = static_cast<int>(fortSizeList.getDoubles()[0]);
	});
	registerKeyword(std::regex("naval_base"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::doubleList navalBaseSizeList(theStream);
		navalBaseLevel = static_cast<int>(navalBaseSizeList.getDoubles()[0]);
	});
	registerKeyword(std::regex("railroad"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::doubleList railSizeList(theStream);
		railLevel = static_cast<int>(railSizeList.getDoubles()[0]);
	});
	registerKeyword(std::regex("aristocrats"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("artisans"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("bureaucrats"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("capitalists"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("clergymen"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("craftsmen"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("clerks"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("farmers"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("soldiers"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("officers"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("labourers"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("slaves"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});
	registerKeyword(std::regex("serfs"), [this](const std::string& popType, std::istream& theStream) {
		Pop pop(popType, theStream);
		pops.push_back(pop);
	});	
	registerKeyword(std::regex("goods_type"),  [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString rgoString(theStream);
		rgo = rgoString.getString();
		if (rgo.substr(0, 1) == "\"")
		{
			rgo = rgo.substr(1, rgo.size() - 2);
		}
	});
	registerKeyword(std::regex("name"),  [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
		if (name.substr(0, 1) == "\"")
		{
			name = name.substr(1, name.size() - 2);
		}
	});

	// ignored items
	registerKeyword(std::regex("controller"), commonItems::ignoreItem);
	registerKeyword(std::regex("garrison"), commonItems::ignoreItem);
	registerKeyword(std::regex("building_construction"), commonItems::ignoreItem);
	registerKeyword(std::regex("life_rating"), commonItems::ignoreItem);
	registerKeyword(std::regex("infrastructure"), commonItems::ignoreItem);
	registerKeyword(std::regex("last_imigration"), commonItems::ignoreItem);
	registerKeyword(std::regex("last_controller_change"), commonItems::ignoreItem);
	registerKeyword(std::regex("unit_names"), commonItems::ignoreItem);
	registerKeyword(std::regex("party_loyalty"), commonItems::ignoreItem);
	registerKeyword(std::regex("modifier"), commonItems::ignoreItem);
	registerKeyword(std::regex("military_construction"), commonItems::ignoreItem);
	registerKeyword(std::regex("crime"), commonItems::ignoreItem);
	registerKeyword(std::regex("nationalism"), commonItems::ignoreItem);
	registerKeyword(std::regex("colonial"), commonItems::ignoreItem);
	registerKeyword(std::regex("flags"), commonItems::ignoreItem);
	registerKeyword(std::regex("rgo"), commonItems::ignoreItem);

	parseStream(theStream);
	identifier = name + " (" + std::to_string(number) + ")";
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
