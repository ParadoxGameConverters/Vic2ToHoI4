#include "src/OutHoi4/UnitMedals/OutUnitMedals.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>
#include <stdexcept>



void HoI4::OutputUnitMedals(std::filesystem::path output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_unit_medals)
{
	std::filesystem::create_directories("output" / output_name / "common/unit_medals");

	const std::filesystem::path path = "output" / output_name / "common/unit_medals/00_default.txt";
	std::ofstream out(path);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + path.string());
	}

	out << "@cost = 30\n";
	out << "\n";
	out << "unit_medals = {\n";

	for (const auto& ideology: major_ideologies)
	{
		const auto ideology_to_unit_medals = ideologies_unit_medals.find(ideology);
		if (ideology_to_unit_medals == ideologies_unit_medals.end())
		{
			continue;
		}

		out << ideology_to_unit_medals->second << "\n\n";
	}

	out << "}";
}
