#include "src/OutHoi4/Landmarks/OutLandmarkBuildings.h"
#include "external/common_items/Log.h"
#include "src/OutHoi4/Landmarks/OutLandmark.h"
#include <fstream>
#include <ranges>


void HoI4::outputLandmarkBuildings(const LandmarkBuildings& landmarkBuildings, const std::string& outputName)
{
	std::ofstream out("output/" + outputName + "/common/buildings/01_landmark_buildings.txt");
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open output/" + outputName + "/common/buildings/01_landmark_buildings.txt");
	}

	out << landmarkBuildings;
	out.close();
}

std::ostream& HoI4::operator<<(std::ostream& outStream, const HoI4::LandmarkBuildings& outLandmarkBuildings)
{
	for (const auto& [key, value]: outLandmarkBuildings.getConstants())
	{
		outStream << key << " = " << value << "\n";
	}
	outStream << "\n";

	outStream << "buildings = {\n";
	for (const auto& building: outLandmarkBuildings.getBuildings())
	{
		outStream << "\n";
		outStream << building;
	}
	outStream << "}\n";
	outStream << "\n";

	outStream << "spawn_points " << outLandmarkBuildings.getSpawnPoints();

	return outStream;
}