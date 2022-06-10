#include "src/OutHoi4/Military/OutRegimentType.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& out, const RegimentType& regiment)
{
	out << "\t\t" << regiment.type << " = { x = " << regiment.x << " y = " << regiment.y << " }\n";

	return out;
}
