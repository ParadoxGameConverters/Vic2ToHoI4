#include "OutTankDesign.h"



std::ostream& HoI4::operator<<(std::ostream& output, const TankDesign& theDesign)
{
	output << "\tcreate_equipment_variant = {\n";
	output << "\t\tname = \"" << theDesign.name << "\"\n";
	output << "\t\ttype = " << theDesign.type << "\n";
	output << "\t\tparent_version = 0\n";
	if (theDesign.modules)
	{
		output << *theDesign.modules;
	}
	if (theDesign.upgrades)
	{
		output << *theDesign.upgrades;
	}
	if (theDesign.obsolete)
	{
		output << "\t\tobsolete = yes\n";
	}
	if (theDesign.icon)
	{
		output << "\t\ticon = \"" << *theDesign.icon << "\"\n";
	}
	output << "\t}\n";
	return output;
}