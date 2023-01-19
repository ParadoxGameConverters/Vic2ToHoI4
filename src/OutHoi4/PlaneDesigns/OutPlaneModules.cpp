#include "src/OutHoi4/PlaneDesigns/OutPlaneModules.h"



std::ostream& HoI4::operator<<(std::ostream& output, const PlaneModules& the_modules)
{
	output << "\t\tmodules = {\n";
	for (const auto& module: the_modules.modules_)
	{
		output << "\t\t\t" << module.first << " = " << module.second << "\n";
	}
	output << "\t\t}\n";

	return output;
}