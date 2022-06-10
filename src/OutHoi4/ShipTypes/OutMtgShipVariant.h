#ifndef OUT_MTG_SHIP_VARIANT
#define OUT_MTG_SHIP_VARIANT



#include "src/HOI4World/ShipTypes/MtgShipVariant.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const MtgShipVariant& theVariant);

}



#endif // OUT_MTG_SHIP_VARIANT