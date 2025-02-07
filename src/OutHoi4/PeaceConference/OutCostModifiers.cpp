#include "src/OutHoi4/PeaceConference/OutCostModifiers.h"
#include <fstream>
#include <stdexcept>



void HoI4::OutputCostModifiers(std::filesystem::path output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_to_cost_modifiers)
{
	const std::filesystem::path filename =
		 "output" / output_name / "common/peace_conference/cost_modifiers/converter_ideology_peace.txt";
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + filename.string());
	}

	out << "peace_action_modifiers = {\n";

	for (const auto& ideology: major_ideologies)
	{
		const auto ideology_to_cost_modifier = ideologies_to_cost_modifiers.find(ideology);
		if (ideology_to_cost_modifier == ideologies_to_cost_modifiers.end())
		{
			continue;
		}

		out << ideology_to_cost_modifier->second << "\n\n";
	}

	out << "}";
}
