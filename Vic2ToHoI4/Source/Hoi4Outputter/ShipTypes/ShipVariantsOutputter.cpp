#include "ShipVariantsOutputter.h"



std::ostream& HoI4::operator<<(std::ostream& output, const ShipVariants& theVariants)
{
	output << "### VARIANTS ###\n";
	output << "if = {\n";
	output << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	for (const auto& variant: theVariants.legacyVariants)
	{
		output << variant.second;
	}
	output << "}\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	for (const auto& variant: theVariants.mtgVariants)
	{
		output << variant.second;
	}
	output << "}\n";

	return output;
}