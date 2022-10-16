#include "src/OutHoi4/PeaceConference/OutAiPeace.h"
#include <fstream>
#include <stdexcept>



void HoI4::OutputAiPeace(std::string_view output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_to_ai_peace)
{
	std::ofstream out(
		 "output/" + std::string(output_name) + "/common/peace_conference/ai_peace/converter_ideology_peace.txt");
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create output/" + std::string(output_name) +
										 "/common/peace_conference/ai_peace/converter_ideology_peace.txt");
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

	out << "}";
}
