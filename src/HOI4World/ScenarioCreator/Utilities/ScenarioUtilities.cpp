#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include "external/common_items/Log.h"
#include <filesystem>
#include <fstream>

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

const std::string GetFileBufferStr(const std::string& input_file, const std::string folder, const std::string path)
{
	std::string file = path + "/" + folder + "/" + input_file;
	std::stringstream buffer_stream = GetStreamFromFile(file);
	return buffer_stream.str();
}
