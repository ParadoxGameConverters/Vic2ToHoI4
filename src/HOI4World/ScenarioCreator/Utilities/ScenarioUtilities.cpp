#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include <filesystem>

// Initalize static constants
const std::string ScenarioUtilities::garrison = "GARRISON";

const std::string ScenarioUtilities::getSaveName(const std::string& inputFile)
{
	const auto& match = std::filesystem::path::preferred_separator;
	if (const auto& i = inputFile.find(match); i != std::string::npos)
		return getSaveName(inputFile.substr(i + 1));
	else
		return inputFile.substr(0, inputFile.size() - 3);
}

