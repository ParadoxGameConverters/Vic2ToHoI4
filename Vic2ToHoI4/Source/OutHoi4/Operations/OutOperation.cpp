#include "OutOperation.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Operation& operation)
{
	out << operation.getName() << " = {\n";
	out << "}\n";
	out << "\n";

	return out;
}