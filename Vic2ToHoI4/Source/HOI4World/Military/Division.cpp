#include "Division.h"
#include <iomanip>



HoI4::DivisionType::DivisionType(const std::string& _name, const std::string& _type, int _location, double _experience):
	name(_name),
	type(_type),
	location(_location),
	experience(_experience)
{
}


std::ostream& HoI4::operator << (std::ostream& out, const HoI4::DivisionType& division)
{
	out << std::fixed << std::setprecision(1);

	out << "\tdivision = {\n";
	out << "\t\tname = \"" << division.name << "\"\n";
	out << "\t\tlocation = " << division.location << "\n";
	out << "\t\tdivision_template = \"" << division.type << "\"\n";
	out << "\t\tstart_experience_factor = " << division.experience << "\n";
	out << "\t\tstart_equipment_factor = 0.7\n";
	out << "\t}\n";

	return out;
}
