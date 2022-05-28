#ifndef OUT_LEGACY_NAVY_NAMES_H
#define OUT_LEGACY_NAVY_NAMES_H



#include "HOI4World/Navies/LegacyShipTypeNames.h"
#include <ostream>
#include <set>



namespace HoI4
{

void outLegacyNavyNames(std::ostream& out, const std::set<LegacyShipTypeNames>& navyNames, std::string_view tag);

} // namespace HoI4



#endif // OUT_LEGACY_NAVY_NAMES_H