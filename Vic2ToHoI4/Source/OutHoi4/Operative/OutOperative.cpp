#include "OutOperative.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& out, const Operative& operative)
{
	out << "\tcreate_operative_leader = {\n";
	out << "\t\tname = \"" << operative.getName() << "\"\n";
	out << "\t\tGFX = " << operative.getPortrait() << "\n";
	out << "\t\ttraits = {}\n";
	out << "\t\tbypass_recruitment = no\n";
	out << "\t\tavailable_to_spy_master = yes\n";
	if (operative.isFemale())
	{
		out << "\t\tfemale = yes\n";
	}
	out << "\t\tnationalities = { " << operative.getNationality() << " }\n";
	out << "\t}\n";

	return out;
}