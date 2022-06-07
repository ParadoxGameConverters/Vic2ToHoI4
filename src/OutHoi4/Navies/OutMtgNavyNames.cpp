#include "OutMtgNavyNames.h"
#include "src/HOI4World/Navies/NavyNames.h"
#include "OutMtgShipTypeNames.h"



void HoI4::outMtgNavyNames(std::ostream& out, const std::set<MtgShipTypeNames>& navyNames, const std::string_view tag)
{
	for (const auto& shipTypeNames: navyNames)
	{
		outMtgShipTypeNames(out, shipTypeNames, tag);
	}
}