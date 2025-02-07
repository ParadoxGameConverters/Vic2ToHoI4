#include "src/OutHoi4/Map/OutRailways.h"
#include "src/OutHoi4/Map/OutRailway.h"
#include <fstream>



void HoI4::outputRailways(const std::filesystem::path& path, const std::vector<Railway>& railways)
{
	const auto filePath = path / "map/railways.txt";
	std::ofstream out(filePath);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + filePath.string());
	}

	for (const auto& railway: railways)
	{
		out << railway;
	}

	out.close();
}