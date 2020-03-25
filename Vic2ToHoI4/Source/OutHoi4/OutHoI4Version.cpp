#include "OutHoI4Version.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& out, const HoI4::Version& version)
{
	out << version.first << '.' << version.second << '.' << version.third;

	return out;
}