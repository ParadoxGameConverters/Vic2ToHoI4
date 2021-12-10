#include "OutRailways.h"
#include "OutHoi4/Map/OutRailway.h"
#include <fstream>



void HoI4::outputRailways(const std::string& path, const std::vector<Railway>& railways)
{
	std::ofstream out(path + "/map/railways.txt");
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + path + "/map/railways.txt");
	}

	for (const auto& railway: railways)
	{
		out << railway;
	}

	out.close();
}