#include "OutLegacyNavyNames.h"
#include "OutLegacyShipTypeNames.h"
#include "../../HOI4World/Navies/NavyNames.h"



void HoI4::outLegacyNavyNames(
	std::ostream& out,
	const std::set<LegacyShipTypeNames>& navyNames,
	const std::string_view tag
)
{
	out << tag << " = {\n";
	for (const auto& shipTypeNames: navyNames)
	{
		outLegacyShipTypeNames(out, shipTypeNames);
	}
	out << "}\n";
}