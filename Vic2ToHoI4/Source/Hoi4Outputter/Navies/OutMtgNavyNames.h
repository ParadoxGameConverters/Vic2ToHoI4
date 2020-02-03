#ifndef OUT_MTG_NAVY_NAMES_H
#define OUT_MTG_NAVY_NAMES_H



#include <ostream>
#include <set>
#include <string>



namespace HoI4
{

class MtgShipTypeNames;

void outMtgNavyNames(std::ostream& out, const std::set<MtgShipTypeNames>& navyNames, std::string_view tag);

}



#endif // OUT_MTG_NAVY_NAMES_H