#include "src/OutHoi4/Map/OutBuildings.h"
#include "src/OutHoi4/Map/OutBuilding.h"
#include <fstream>
#include <ranges>


void HoI4::outputBuildings(const Buildings& buildings, const std::string& outputName)
{
	std::ofstream out("output/" + outputName + "/map/buildings.txt");
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open output/" + outputName + "/map/buildings.txt");
	}
	for (const auto& building: buildings.getBuildings() | std::views::values)
	{
		out << building;
	}
	out.close();
}
