#include "src/OutHoi4/PlaneDesigns/OutPlaneDesigns.h"
#include <ranges>



std::ostream& HoI4::operator<<(std::ostream& output, const PlaneDesigns& theDesigns)
{
	output << "### PLANE DESIGNS ###\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	for (const auto& design: theDesigns.planeDesigns | std::views::values)
	{
		output << design;
	}
	output << "}\n";

	return output;
}
