#include "OutDivisionType.h"
#include <iomanip>



std::ostream& HoI4::operator<<(std::ostream& out, const DivisionType& division)
{
	out << std::fixed << std::setprecision(1);

	out << "\tdivision = {\n";
	out << "\t\tname = \"" << division.name << "\"\n";
	out << "\t\tlocation = " << division.location << "\n";
	out << "\t\tdivision_template = \"" << division.type << "\"\n";
	out << "\t\tstart_experience_factor = " << division.experience << "\n";
	out << "\t\tstart_equipment_factor = " << division.startEquipment << "\n";
	out << "\t}\n";

	return out;
}