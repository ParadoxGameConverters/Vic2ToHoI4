#include "src/OutHoi4/Map/OutRailway.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Railway& railway)
{
	out << railway.getLevel() << " " << railway.getLength();
	for (const int province: railway.getProvinces())
	{
		out << " " << province;
	}
	out << "\n";

	return out;
}