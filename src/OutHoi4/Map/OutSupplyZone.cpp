#include "src/OutHoi4/Map/OutSupplyZone.h"
#include <fstream>



void HoI4::outputSupplyZone(const SupplyZone& supplyZone,
	 const std::filesystem::path& filename,
	 const std::filesystem::path& outputName)
{
	const auto fullFilename("output" / outputName / "map/supplyareas" / filename);
	std::ofstream out(fullFilename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + ("output/input/map/supplyareas/" / filename).string());
	}
	out << "\n";
	out << "supply_area={\n";
	out << "\tid=" << supplyZone.getId() << "\n";
	out << "\tname=\"SUPPLYAREA_" << supplyZone.getId() << "\"\n";
	out << "\tvalue=" << supplyZone.getValue() << "\n";
	out << "\tstates={\n";
	out << "\t\t";
	for (auto stateNum: supplyZone.getStates())
	{
		out << stateNum << " ";
	}
	out << std::endl;
	out << "\t}\n";
	out << "}\n";

	out.close();
}