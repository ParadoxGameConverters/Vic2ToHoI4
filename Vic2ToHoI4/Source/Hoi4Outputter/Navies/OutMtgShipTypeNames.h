#ifndef OUT_MTG_SHIP_TYPE_NAMES
#define OUT_MTG_SHIP_TYPE_NAMES



#include <ostream>
#include <string>



namespace HoI4
{
	
class MtgShipTypeNames;

void outMtgShipTypeNames(std::ostream& out, const MtgShipTypeNames& shipTypeNames, std::string_view tag);

}




#endif // OUT_MTG_SHIP_TYPE_NAMES