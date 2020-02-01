#include "OutSupplyZone.h"
#include "Log.h"
#include <fstream>



void HoI4::outputSupplyZone(
	const HoI4SupplyZone& supplyZone,
	const std::string& filename,
	const Configuration& theConfiguration
)
{
	std::string fullFilename("output/" + theConfiguration.getOutputName() + "/map/supplyareas/" + filename);
	std::ofstream out(fullFilename);
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not open \"output/input/map/supplyareas/" + filename;
		exit(-1);
	}
	out << "\n";
	out << "supply_area={" << std::endl;
	out << "\tid=" << supplyZone.getId() << std::endl;
	out << "\tname=\"SUPPLYAREA_" << supplyZone.getId() << "\"" << std::endl;
	out << "\tvalue=" << supplyZone.getValue() << std::endl;
	out << "\tstates={" << std::endl;
	out << "\t\t";
	for (auto stateNum: supplyZone.getStates())
	{
		out << stateNum << " ";
	}
	out << std::endl;
	out << "\t}" << std::endl;
	out << "}" << std::endl;

	out.close();
}