#ifndef OUT_LEGACY_NAVY_NAMES_H
#define OUT_LEGACY_NAVY_NAMES_H



#include <ostream>
#include <set>
#include <string>



namespace HoI4
{

class LegacyShipTypeNames;

void outLegacyNavyNames(std::ostream& out, const std::set<LegacyShipTypeNames>& navyNames, std::string_view tag);

}



#endif // OUT_LEGACY_NAVY_NAMES_H