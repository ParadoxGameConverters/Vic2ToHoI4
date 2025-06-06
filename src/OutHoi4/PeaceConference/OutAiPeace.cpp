#include "src/OutHoi4/PeaceConference/OutAiPeace.h"
#include <fstream>
#include <stdexcept>



void HoI4::OutputAiPeace(std::filesystem::path output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_to_ai_peace,
	 const std::vector<std::string>& dynamic_ai_peaces)
{
	const std::filesystem::path filename =
		 "output" / output_name / "common/peace_conference/ai_peace/converter_ideology_peace.txt";
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + filename.string());
	}

	out << "peace_ai_desires = {\n";

	for (const auto& ideology: major_ideologies)
	{
		const auto ideology_to_ai_peace = ideologies_to_ai_peace.find(ideology);
		if (ideology_to_ai_peace == ideologies_to_ai_peace.end())
		{
			continue;
		}

		out << ideology_to_ai_peace->second << "\n\n";
	}

	for (const auto& dynamic_ai_peace: dynamic_ai_peaces)
	{
		out << dynamic_ai_peace << "\n\n";
	}

	out << "}";
}
