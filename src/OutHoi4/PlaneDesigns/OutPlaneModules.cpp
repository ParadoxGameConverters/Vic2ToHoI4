#include "src/OutHoi4/PlaneDesigns/OutPlaneModules.h"



std::ostream& HoI4::operator<<(std::ostream& output, const PlaneModules& theModules)
{
	output << "\t\tmodules = {\n";
	for (const auto& module: theModules.modules)
	{
		output << "\t\t\t" << module.first << " = " << module.second << "\n";
	}
	output << "\t\t}\n";

	return output;
}