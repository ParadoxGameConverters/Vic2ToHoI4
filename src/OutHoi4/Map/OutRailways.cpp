#include "OutRailways.h"
#include "src/OutHoi4/Map/OutRailway.h"
#include <fstream>



void HoI4::outputRailways(const std::string& path, const std::vector<Railway>& railways)
{
	const auto filePath = path + "/map/railways.txt";
	std::ofstream out(filePath);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + filePath);
	}

	for (const auto& railway: railways)
	{
		out << railway;
	}

	out.close();
}