#include "src/OutHoi4/Navies/OutLegacyNavyNames.h"
#include "src/HOI4World/Navies/NavyNames.h"
#include "src/OutHoi4/Navies/OutLegacyShipTypeNames.h"



void HoI4::outLegacyNavyNames(std::ostream& out,
	 const std::set<LegacyShipTypeNames>& navyNames,
	 const std::string_view tag)
{
	out << tag << " = {\n";
	for (const auto& shipTypeNames: navyNames)
	{
		outLegacyShipTypeNames(out, shipTypeNames);
	}
	out << "}\n";
}