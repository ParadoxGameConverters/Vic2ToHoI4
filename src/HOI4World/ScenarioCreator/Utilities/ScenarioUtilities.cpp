#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include "external/common_items/Log.h"
#include <filesystem>
#include <fstream>

bool IdeologySituation::operator>(const IdeologySituation& rhs) const
{
	return (is_gov_ && !rhs.is_gov_) || support_ > rhs.support_;
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

const std::string GetFileBufferStr(const std::string& input_file, const std::string folder, const std::string path)
{
	std::string file = path + "/" + folder + "/" + input_file;
	std::stringstream buffer_stream = GetStreamFromFile(file);
	return buffer_stream.str();
}

const IdeologicalSituationSet GetIdeologicalSituation(const std::map<std::string, int> ideology_support,
	 const std::string gov_ideology)
{
	IdeologicalSituationSet ideological_situation;
	ideological_situation.emplace(gov_ideology, ideology_support.at(gov_ideology), true);

	for (const auto& ideology: ideology_support)
	{
		if (ideology.first != gov_ideology)
		{
			ideological_situation.emplace(ideology.first,ideology.second);
		}
	}

	return ideological_situation;
}
