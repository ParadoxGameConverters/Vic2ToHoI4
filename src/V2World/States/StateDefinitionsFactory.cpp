#include "StateDefinitionsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"



Vic2::StateDefinitions::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& stateID, std::istream& theStream) {
		const auto provinceNumbers = commonItems::intList{theStream}.getInts();

		std::set<int> neighbors;
		for (auto provinceNumber: provinceNumbers)
		{
			neighbors.insert(provinceNumber);
			stateDefinitions->provinceToIDMap.insert(std::make_pair(provinceNumber, stateID));
		}

		for (auto neighbor: neighbors)
		{
			stateDefinitions->stateMap.insert(make_pair(neighbor, neighbors));
		}

		if (!provinceNumbers.empty())
		{
			stateDefinitions->stateToCapitalMap.insert(std::make_pair(stateID, provinceNumbers.front()));
		}
	});
}


std::unique_ptr<Vic2::StateDefinitions> Vic2::StateDefinitions::Factory::getStateDefinitions(
	 const Configuration& theConfiguration)
{
	stateDefinitions = std::make_unique<StateDefinitions>();

	Log(LogLevel::Info) << "Importing Vic2 states";
	auto stateMapInitialized = false;
	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		const auto regionFileName = mod.path + "/map/region.txt";
		if (commonItems::DoesFileExist(regionFileName))
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

	return std::move(stateDefinitions);
}