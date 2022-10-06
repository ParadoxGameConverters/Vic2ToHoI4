#include "src/OutHoi4/PlaneDesigns/OutPlaneDesign.h"



std::ostream& HoI4::operator<<(std::ostream& output, const PlaneDesign& the_design)
{
	output << "\tcreate_equipment_variant = {\n";
	output << "\t\tname = \"" << the_design.name_ << "\"\n";
	output << "\t\ttype = " << the_design.type_ << "\n";
	if (the_design.modules_)
	{
		output << *the_design.modules_;
	}
	if (the_design.obsolete_)
	{
		output << "\t\tobsolete = yes\n";
	}
	if (the_design.icon_)
	{
		output << "\t\ticon = \"" << *the_design.icon_ << "\"\n";
	}
	output << "\t}\n";
	return output;
}