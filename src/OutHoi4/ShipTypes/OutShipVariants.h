#ifndef OUT_SHIP_VARIANTS_H
#define OUT_SHIP_VARIANTS_H



#include "src/HOI4World/ShipTypes/ShipVariants.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const ShipVariants& theVariants);

}



#endif // OUT_SHIP_VARIANTS_H