#include "src/OutHoi4/Map/OutBuilding.h"
#include <iomanip>



std::ostream& HoI4::operator<<(std::ostream& out, const Building& building)
{
	out << building.stateID << ";" << building.type << ";";
	out << std::fixed << std::setprecision(2) << building.position.xCoordinate << ';' << building.position.yCoordinate
		 << ';' << building.position.zCoordinate << ';' << building.position.rotation << ';';
	out << building.connectingSeaProvince << '\n';

	return out;
}