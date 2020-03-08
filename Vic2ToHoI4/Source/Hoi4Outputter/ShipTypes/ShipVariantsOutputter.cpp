#include "ShipVariantsOutputter.h"



std::ostream& HoI4::operator<<(std::ostream& output, const shipVariants& theVariants)
{
	output << "### VARIANTS ###\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	for (auto variant: theVariants.mtgVariants)
	{
		output << variant.second;
	}
	output << "}\n";

	return output;
}