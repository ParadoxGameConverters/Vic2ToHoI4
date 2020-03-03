#include "OutAirplane.h"



std::ostream& HoI4::operator<<(std::ostream& output, const Airplane& instance)
{
	output << "\t\t" << instance.type << " = {\n";
	output << "\t\t\towner = \"" << instance.owner << "\"\n";
	output << "\t\t\tamount = " << instance.amount << "\n";
	output << "\t\t}\n";

	return output;
}