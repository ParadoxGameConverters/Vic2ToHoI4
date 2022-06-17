#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include "external/common_items/Log.h"
#include <filesystem>
#include <fstream>

const std::string GetSaveName(const std::string& input_file)
{
	// warning C4244: 'argument': conversion from 'const wchar_t' to 'const _Elem', possible loss of data
	// TODO: Take a look at this by end of June
	const auto& match = std::filesystem::path::preferred_separator;
	if (const auto& i = input_file.find(match); i != std::string::npos)
		return GetSaveName(input_file.substr(i + 1));
	else
		return input_file.substr(0, input_file.size() - 3);
}

const std::stringstream GetStreamFromFile(const std::string& input_file)
{
	std::ifstream the_file(std::filesystem::u8path(input_file));
	if (!the_file.is_open())
	{
		Log(LogLevel::Error) << "Could not open " << input_file << " for parsing.";
		return std::stringstream();
	}

	std::stringstream buf_stream;
	buf_stream << the_file.rdbuf();

	the_file.close();

	return buf_stream;
}
