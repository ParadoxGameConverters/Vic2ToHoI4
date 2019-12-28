#ifndef SHIP_VARIANT_OUTPUTTER_H
#define SHIP_VARIANT_OUTPUTTER_H



#include "../../HOI4World//ShipTypes/ShipVariant.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator<<(std::ostream& output, shipVariant& theVariant);
}



#endif // SHIP_VARIANT_OUTPUTTER_H