#ifndef OUT_MTG_SHIP_TYPE_NAMES_H
#define OUT_MTG_SHIP_TYPE_NAMES_H



#include <ostream>
#include <string>



namespace HoI4
{

class MtgShipTypeNames;

void outMtgShipTypeNames(std::ostream& out, const MtgShipTypeNames& shipTypeNames, std::string_view tag);

} // namespace HoI4



#endif // OUT_MTG_SHIP_TYPE_NAMES_H