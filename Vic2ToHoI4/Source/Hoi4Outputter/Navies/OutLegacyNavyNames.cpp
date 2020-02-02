#include "OutLegacyNavyNames.h"
#include "OutLegacyShipTypeNames.h"
#include "../../HOI4World/Navies/NavyNames.h"



void HoI4::outLegacyNavyNames(std::ostream& out, const NavyNames& navyNames, const std::string_view tag)
{
	out << tag << " = {\n";
	for (const auto& shipTypeNames: navyNames.getShipTypeNames())
	{
		outLegacyShipTypeNames(out, shipTypeNames);
	}
	out << "}\n";
}