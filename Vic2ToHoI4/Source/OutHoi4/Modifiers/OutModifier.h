#ifndef OUT_MODIFIER_H
#define OUT_MODIFIER_H

#include "HOI4World/Modifiers/Modifier.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const Modifier& modifier);

} // namespace HoI4



#endif // OUT_MODIFIER_H