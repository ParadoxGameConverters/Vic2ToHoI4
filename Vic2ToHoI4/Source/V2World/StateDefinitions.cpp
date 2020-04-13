#include "StateDefinitions.h"
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



std::unique_ptr<Vic2::StateDefinitions> Vic2::StateDefinitions::Parser::parseStateDefinitions(
	 const Configuration& theConfiguration)
{
	std::map<int, std::set<int>> stateMap; // < province, all other provinces in state >
	std::map<int, std::string> provinceToIDMap;
	std::map<std::string, int> stateToCapitalMap;

	registerKeyword(std::regex("[A-Z0-9\\_]+"),
		 [&stateMap, &provinceToIDMap, &stateToCapitalMap](const std::string& stateID, std::istream& theStream) {
			 const commonItems::intList provinceNumbersList(theStream);
			 const auto provinceNumbers = provinceNumbersList.getInts();

			 std::set<int> neighbors;
			 for (auto provinceNumber: provinceNumbers)
			 {
				 neighbors.insert(provinceNumber);
				 provinceToIDMap.insert(std::make_pair(provinceNumber, stateID));
			 }

			 for (auto neighbor: neighbors)
			 {
				 stateMap.insert(make_pair(neighbor, neighbors));
			 }

			 if (!provinceNumbers.empty())
			 {
				 stateToCapitalMap.insert(std::make_pair(stateID, provinceNumbers.front()));
			 }
		 });

	LOG(LogLevel::Info) << "Importing Vic2 states";
	auto stateMapInitialized = false;
	for (const auto& itr: theConfiguration.getVic2Mods())
	{
		const auto regionFileName = theConfiguration.getVic2Path() + "/mod/" + itr + "/map/region.txt";
		if (Utils::DoesFileExist(regionFileName))
		{
			parseFile(regionFileName);
			stateMapInitialized = true;
			break;
		}
	}

	if (!stateMapInitialized)
	{
		parseFile(theConfiguration.getVic2Path() + "/map/region.txt");
	}

	return std::make_unique<StateDefinitions>(stateMap, provinceToIDMap, stateToCapitalMap);
}


std::set<int> Vic2::StateDefinitions::getAllProvinces(const int provinceNumber) const
{
	if (const auto mapping = stateMap.find(provinceNumber); mapping != stateMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::set<int>{};
	}
}


std::optional<std::string> Vic2::StateDefinitions::getStateID(const int provinceNumber) const
{
	if (const auto mapping = provinceToIDMap.find(provinceNumber); mapping != provinceToIDMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}


std::optional<int> Vic2::StateDefinitions::getCapitalProvince(const std::string& stateID) const
{
	if (const auto mapping = stateToCapitalMap.find(stateID); mapping != stateToCapitalMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}