#include "src/OutHoi4/PlaneDesigns/OutPlaneDesigns.h"
#include <ranges>



std::ostream& HoI4::operator<<(std::ostream& output, const PlaneDesigns& the_designs_)
{
	output << "### PLANE DESIGNS ###\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	for (const auto& design: the_designs_.plane_designs_ | std::views::values)
	{
		output << design;
	}
	output << "}\n";

	return output;
}
