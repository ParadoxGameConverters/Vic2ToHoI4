#ifndef OUT_LEGACY_NAVY_H
#define OUT_LEGACY_NAVY_H



#include "src/HOI4World/Navies/LegacyNavy.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const LegacyNavy& instance);

}



#endif // OUT_LEGACY_NAVY_H