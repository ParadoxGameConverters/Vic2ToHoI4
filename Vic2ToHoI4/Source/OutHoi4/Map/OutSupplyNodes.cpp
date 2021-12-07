#include "OutSupplyNodes.h"

#include <fstream>



void HoI4::outputSupplyNodes(const std::string& path, const std::set<int>& SupplyNodes)
{
	std::ofstream out(path + "/map/supply_nodes.txt");
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + path + "/map/supply_nodes.txt");
	}

	for (const auto& supplyNode: SupplyNodes)
	{
		out << "1 " << supplyNode << "\n";
	}

	out.close();
}