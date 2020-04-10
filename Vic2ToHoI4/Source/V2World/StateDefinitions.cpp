#include "StateDefinitions.h"
#include "Log.h"
#include "../Configuration.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



void Vic2::StateDefinitions::initialize()
{
	registerKeyword(std::regex("[A-Z0-9\\_]+"), [this](const std::string& stateID, std::istream& theStream){
		commonItems::intList provinceNumbers(theStream);

		std::set<int> neighbors;
		for (auto provinceNumber: provinceNumbers.getInts())
		{
			neighbors.insert(provinceNumber);
			provinceToIDMap.insert(std::make_pair(provinceNumber, stateID));
		}

		for (auto neighbor: neighbors)
		{
			stateMap.insert(make_pair(neighbor, neighbors));
		}

		if (provinceNumbers.getInts().size() > 0)
		{
			stateToCapitalMap.insert(std::make_pair(stateID, provinceNumbers.getInts().front()));
		}
	});

	LOG(LogLevel::Info) << "Importing Vic2 states";
	bool stateMapInitialized = false;
	for (auto itr: theConfiguration.getVic2Mods())
	{
		std::string regionFileName = theConfiguration.getVic2Path() + "/mod/" + itr + "/map/region.txt";
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
}


std::set<int> Vic2::StateDefinitions::getAllProvinces(int provinceNumber) const
{
	if (auto mapping = stateMap.find(provinceNumber); mapping != stateMap.end())
	{
		return mapping->second;
	}
	else
	{
		std::set<int> empty;
		return empty;
	}
}


std::optional<std::string> Vic2::StateDefinitions::getStateID(int provinceNumber) const
{
	if (auto mapping = provinceToIDMap.find(provinceNumber); mapping != provinceToIDMap.end())
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
	if (auto mapping = stateToCapitalMap.find(stateID); mapping != stateToCapitalMap.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}