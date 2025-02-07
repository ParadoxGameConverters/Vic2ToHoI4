#include "src/OutHoi4/Landmarks/OutLandmarkBuildings.h"
#include "external/common_items/Log.h"
#include "src/OutHoi4/Landmarks/OutLandmark.h"
#include <fstream>
#include <ranges>


void HoI4::outputLandmarkBuildings(const LandmarkBuildings& landmarkBuildings, const std::filesystem::path& outputName)
{
	const std::filesystem::path folder = "output" / outputName / "common/buildings";
	std::filesystem::create_directories(folder);

	const std::filesystem::path filename = folder / "01_landmark_buildings.txt";
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + filename.string());
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
	for (const auto& building: outLandmarkBuildings.getBuildings() | std::views::values)
	{
		outStream << "\n";
		outStream << *building;
	}
	outStream << "}\n";
	outStream << "\n";

	outStream << "spawn_points " << outLandmarkBuildings.getSpawnPoints();

	return outStream;
}