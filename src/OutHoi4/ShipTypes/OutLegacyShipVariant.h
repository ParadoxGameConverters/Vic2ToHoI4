#ifndef OUT_LEGACY_SHIP_VARIANT_H
#define OUT_LEGACY_SHIP_VARIANT_H



#include "src/HOI4World/ShipTypes/LegacyShipVariant.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const LegacyShipVariant& theVariant);

}



#endif // OUT_LEGACY_SHIP_VARIANT_H