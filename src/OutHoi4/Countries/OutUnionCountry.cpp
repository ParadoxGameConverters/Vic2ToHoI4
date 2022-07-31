#include "OutUnionCountry.h"



std::ostream& HoI4::operator<<(std::ostream& out, const UnionCountry& country)
{
	out << country.GetTag() << "= {\n";
	out << "\tcolor " << country.GetColor().outputRgb() << "\n";
	out << "\tcolor_ui " << country.GetColor().outputRgb() << "\n";
	out << "}\n";
	out << "\n";

	return out;
}