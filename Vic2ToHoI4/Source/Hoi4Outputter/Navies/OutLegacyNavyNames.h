#ifndef OUT_LEGACY_NAVY_NAMES_H
#define OUT_LEGACY_NAVY_NAMES_H



#include <ostream>
#include <set>
#include <string>



namespace HoI4
{

class ShipTypeNames;

void outLegacyNavyNames(std::ostream& out, const std::set<ShipTypeNames>& navyNames, std::string_view tag);

}



#endif // OUT_LEGACY_NAVY_NAMES_H