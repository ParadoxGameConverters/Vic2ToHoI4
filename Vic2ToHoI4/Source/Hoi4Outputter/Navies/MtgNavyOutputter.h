#ifndef MTG_NAVY_OUTPUTTER
#define MTG_NAVY_OUTPUTTER



#include "../../HOI4World/Navies/MtgNavy.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator << (std::ostream& output, const MtgNavy& instance);
}



#endif //MTG_NAVY_OUTPUTTER