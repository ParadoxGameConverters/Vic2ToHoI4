#include "OutMtgShipVariant.h"



std::ostream& HoI4::operator<<(std::ostream& output, const MtgShipVariant& theVariant)
{
	output << "\tcreate_equipment_variant = {\n";
	output << "\t\tname = \"" << theVariant.name << "\"\n";
	output << "\t\ttype = " << theVariant.type << "\n";
	output << "\t\tname_group = " << theVariant.owningCountryTag << "_" << theVariant.nameGroup << "\n";
	output << "\t\tparent_version = 0\n";
	if (theVariant.modules)
	{
		output << *theVariant.modules;
	}
	if (theVariant.obsolete)
	{
		output << "\t\tobsolete = yes\n";
	}
	output << "\t}\n";
	return output;
}