#include "OutSupplyNodes.h"

#include <fstream>



void HoI4::outputSupplyNodes(const std::string& path, const std::set<int>& SupplyNodes)
{
	const auto filePath = path + "/map/supply_nodes.txt";
	std::ofstream out(filePath);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + filePath);
	}

	for (const auto& supplyNode: SupplyNodes)
	{
		out << "1 " << supplyNode << "\n";
	}

	out.close();
}