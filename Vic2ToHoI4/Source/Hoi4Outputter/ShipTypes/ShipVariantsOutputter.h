#ifndef SHIP_VARIANTS_OUTPUTTER
#define SHIP_VARIANTS_OUTPUTTER



#include "../../HOI4World/ShipTypes/ShipVariants.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator << (std::ostream& output, const shipVariants& theVariants);
}



#endif // SHIP_VARIANTS_OUTPUTTER