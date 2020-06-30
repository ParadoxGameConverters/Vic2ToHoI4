#include "OutOperation.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Operation& operation)
{
	out << " = {\n";
	out << "}\n";
	out << "\n";

	return out;
}