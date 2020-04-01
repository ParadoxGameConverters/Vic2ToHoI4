#include "OutColor.h"



std::ostream& ConverterColor::operator<<(std::ostream& out, const Color& color)
{
	out << color.c[0] << ' ' << color.c[1] << ' ' << color.c[2];

	return out;
}