#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include <filesystem>

const std::string ScenarioUtilities::GetSaveName(const std::string& input_file)
{
	const auto& match = std::filesystem::path::preferred_separator;
	if (const auto& i = input_file.find(match); i != std::string::npos)
		return GetSaveName(input_file.substr(i + 1));
	else
		return input_file.substr(0, input_file.size() - 3);
}
