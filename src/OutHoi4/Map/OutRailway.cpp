#include "src/OutHoi4/Map/OutRailway.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Railway& railway)
{
	out << railway.GetLevel() << " " << railway.GetLength();
	for (const int province: railway.GetProvinces())
	{
		out << " " << province;
	}
	out << "\n";

	return out;
}