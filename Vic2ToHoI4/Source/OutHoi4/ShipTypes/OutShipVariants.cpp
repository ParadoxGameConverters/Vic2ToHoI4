#include "OutShipVariants.h"
#include <ranges>


std::ostream& HoI4::operator<<(std::ostream& output, const ShipVariants& theVariants)
{
	output << "### VARIANTS ###\n";
	output << "if = {\n";
	output << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	for (const auto& variant: theVariants.legacyVariants | std::views::values)
	{
		output << variant;
	}
	output << "}\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	for (const auto& variant: theVariants.mtgVariants | std::views::values)
	{
		output << variant;
	}
	output << "}\n";

	return output;
}
