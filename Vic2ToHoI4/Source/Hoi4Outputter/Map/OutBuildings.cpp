#include "OutBuildings.h"
#include "OutBuilding.h"
#include "Log.h"



void HoI4::outputBuildings(const Buildings& buildings, const Configuration& theConfiguration)
{
	std::ofstream out("output/" + theConfiguration.getOutputName() + "/map/buildings.txt");
	if (!out.is_open())
	{
		throw std::runtime_error(
			"Could not open output/" + theConfiguration.getOutputName() + "/map/buildings.txt"
		);
	}
	for (const auto& building: buildings.getBuildings())
	{
		out << *building.second;
	}
	out.close();

	std::ofstream airportsFile("output/" + theConfiguration.getOutputName() + "/map/airports.txt");
	if (!airportsFile.is_open())
	{
		throw std::runtime_error(
			"Could not create output/" + theConfiguration.getOutputName() + "/map/airports.txt"
		);
		exit(-1);
	}
	for (const auto& airportLocation: buildings.getAirportLocations())
	{
		airportsFile << airportLocation.first << "={" << airportLocation.second << " }\n";
	}
	airportsFile.close();
}