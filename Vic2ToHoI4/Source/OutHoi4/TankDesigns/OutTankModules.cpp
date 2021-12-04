#include "OutTankModules.h"



std::ostream& HoI4::operator<<(std::ostream& output, const TankModules& theModules)
{
	output << "\t\tmodules = {\n";
	for (const auto& module: theModules.modules)
	{
		output << "\t\t\t" << module.first << " = " << module.second << "\n";
	}
	output << "\t\t}\n";

	return output;
}