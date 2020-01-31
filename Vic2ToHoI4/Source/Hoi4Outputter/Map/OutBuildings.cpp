#include "OutBuildings.h"
#include "OutBuilding.h"
#include "Log.h"



void HoI4::outputBuildings(const HoI4::Buildings& buildings, const Configuration& theConfiguration)
{
	std::ofstream out("output/" + theConfiguration.getOutputName() + "/map/buildings.txt");
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not open output/" << theConfiguration.getOutputName() << "/map/buildings.txt";
		exit(-1);
	}

	for (auto building: buildings.getBuildings())
	{
		out << *(building.second);
	}
	out.close();

	std::ofstream airportsFile("output/" + theConfiguration.getOutputName() + "/map/airports.txt");
	if (!airportsFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create output/" << theConfiguration.getOutputName() << "/map/airports.txt";
		exit(-1);
	}
	for (auto airportLocation: buildings.getAirportLocations())
	{
		airportsFile << airportLocation.first << "={" << airportLocation.second << " }\n";
	}
	airportsFile.close();
}