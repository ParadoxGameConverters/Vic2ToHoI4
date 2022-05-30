#ifndef OUT_MTG_NAVY_NAMES_H
#define OUT_MTG_NAVY_NAMES_H



#include "HOI4World/Navies/MtgShipTypeNames.h"
#include <ostream>
#include <set>



namespace HoI4
{

void outMtgNavyNames(std::ostream& out, const std::set<MtgShipTypeNames>& navyNames, std::string_view tag);

} // namespace HoI4



#endif // OUT_MTG_NAVY_NAMES_H