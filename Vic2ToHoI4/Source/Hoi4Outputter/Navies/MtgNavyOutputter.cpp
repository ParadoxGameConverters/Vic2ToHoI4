#include "MtgNavyOutputter.h"



std::ostream& HoI4::operator << (std::ostream& output, const MtgNavy& instance)
{
	output << "\tfleet = {\n";
	output << "\t\tname = \"" << instance.name << "\"\n";
	output << "\t\tnaval_base = " << instance.base << "\n";
	output << "\t\ttask_force = {\n";
	output << "\t\t\tname = \"" << instance.name << "\"\n";
	output << "\t\t\tlocation = " << instance.location << "\n";
	for (auto& ship : instance.ships)
	{
		output << ship;
	}
	output << "\t\t}\n";
	output << "\t}\n";

	return output;
}