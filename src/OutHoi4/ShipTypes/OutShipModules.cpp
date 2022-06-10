#include "src/OutHoi4/ShipTypes/OutShipModules.h"



std::ostream& HoI4::operator<<(std::ostream& output, const shipModules& theModules)
{
	output << "\t\tmodules = {\n";
	for (const auto& module: theModules.modules)
	{
		output << "\t\t\t" << module.first << " = " << module.second << "\n";
	}
	output << "\t\t}\n";

	return output;
}