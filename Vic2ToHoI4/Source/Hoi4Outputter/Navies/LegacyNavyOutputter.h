#ifndef LEGACY_NAVY_OUTPUTTER
#define LEGACY_NAVY_OUTPUTTER



#include "../../HOI4World/Navies/LegacyNavy.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator << (std::ostream& output, const LegacyNavy& instance);
}



#endif // LEGACY_NAVY_OUTPUTTER