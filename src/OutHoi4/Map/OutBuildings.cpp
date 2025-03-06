#include "src/OutHoi4/Map/OutBuildings.h"
#include "src/OutHoi4/Map/OutBuilding.h"
#include <fstream>
#include <ranges>


void HoI4::outputBuildings(const Buildings& buildings, const std::filesystem::path& outputName)
{
	const std::filesystem::path folder = "output" / outputName / "map/buildings.txt";
	std::ofstream out(folder);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + folder.string());
	}
	for (const auto& building: buildings.getBuildings() | std::views::values)
	{
		out << building;
	}
	out.close();
}
