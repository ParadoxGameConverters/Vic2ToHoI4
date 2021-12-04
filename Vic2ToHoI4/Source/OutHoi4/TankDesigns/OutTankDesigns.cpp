#include "OutTankDesigns.h"
#include <ranges>


std::ostream& HoI4::operator<<(std::ostream& output, const TankDesigns& theDesigns)
{
	output << "### TANK DESIGNS ###\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"No Step Back\" }\n";
	for (const auto& design: theDesigns.tankDesigns | std::views::values)
	{
		output << design;
	}
	output << "}\n";

	return output;
}
