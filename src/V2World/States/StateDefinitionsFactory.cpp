#include "src/V2World/States/StateDefinitionsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"



Vic2::StateDefinitions::Factory::Factory()
{
	parser_.registerRegex(commonItems::catchallRegex, [this](const std::string& stateID, std::istream& theStream) {
		const auto provinceNumbers = commonItems::intList{theStream}.getInts();

		std::set<int> neighbors;
		for (auto provinceNumber: provinceNumbers)
		{
			neighbors.insert(provinceNumber);
			state_definitions_->provinceToIDMap.insert(std::make_pair(provinceNumber, stateID));
		}

		for (auto neighbor: neighbors)
		{
			state_definitions_->stateMap.insert(make_pair(neighbor, neighbors));
		}

		if (!provinceNumbers.empty())
		{
			state_definitions_->stateToCapitalMap.insert(std::make_pair(stateID, provinceNumbers.front()));
		}
	});
}


std::unique_ptr<Vic2::StateDefinitions> Vic2::StateDefinitions::Factory::getStateDefinitions(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	Log(LogLevel::Info) << "Importing Vic2 states";

	state_definitions_ = std::make_unique<StateDefinitions>();

	if (const auto& file = mod_filesystem.GetActualFileLocation("map/region.txt"); file)
	{
		parser_.parseFile(*file);
	}

	return std::move(state_definitions_);
}