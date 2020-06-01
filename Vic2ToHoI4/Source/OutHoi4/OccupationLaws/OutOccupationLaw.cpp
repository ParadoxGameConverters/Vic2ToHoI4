#include "OutOccupationLaw.h"



std::ostream& HoI4::operator<<(std::ostream& output, const OccupationLaw& occupationLaw)
{
	output << occupationLaw.getName() << " = {\n";
	output << "}\n";
	output << "\n";

	return output;
}