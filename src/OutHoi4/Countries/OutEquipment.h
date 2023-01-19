#ifndef SRC_OUTHOI4_COUNTRIES_OUTEQUIPMENT_H
#define SRC_OUTHOI4_COUNTRIES_OUTEQUIPMENT_H



#include "src/HOI4World/Countries/Equipment.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const HoI4::Equipment& equipment);

}



#endif // SRC_OUTHOI4_COUNTRIES_OUTEQUIPMENT_H